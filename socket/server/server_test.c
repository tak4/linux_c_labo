#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>	// for pthread_create, pthread_join
#include <unistd.h>		// for close, sleep
#include <sys/socket.h>	// for socket
#include <arpa/inet.h>	// for inet_ntoa
#include <poll.h>		// for poll
#include <signal.h>		// for sigaction

#define MAX_SERVER_THREAD			2		// サーバスレッド数
#define MAX_LISTEN_SOCKET			2		// サーバ接続待ちSocket数
#define	MAX_LISTEN_CONNECT			1		// サーバ listen Socket 最大接続受付数
#define	LISTEN_PORT					12345	// 待ち受けポート番号(開始番号 複数時はインクリメント)
#define MAX_SERVER_THREAD_SOCKET	1		// サーバスレッドSocket数
#define	POLL_WAIT_TIME				3000	// poll待ち付けタイムアウト(ms)
#define	MAX_BUF						256		// 送受信バッファサイズ


// スレッドに渡されるデータ
struct thdata {
	pthread_t th;
	int sock;
};

static void handler(int signo)
{
	printf(" ... Caught the SIGINT (%d)\n", signo);
	exit(EXIT_SUCCESS);
}

void *ServerThread(void *thdata)
{
	int sock = 0;
	int recv_size = 0;
	int	rpoll = 0;
	char recv_buf[MAX_BUF] = { 0 };
	char send_buf[MAX_BUF] = { 0 };
	struct thdata *pthdata = NULL;
	struct pollfd stFds[MAX_SERVER_THREAD_SOCKET];

	// スレッドに渡されるデータ
	pthdata = (struct thdata *)thdata;

	// 送信データ
	strncpy( send_buf, "HELLO", sizeof(send_buf) );

	// Socket生成まで待ち
	while( 1 ) {
		if( 0 == pthdata->sock ) {
			printf("(%lu)Server wait socket initialize...\n", pthdata->th);
			sleep(1);	// 1秒
			continue;
		}
		sock = pthdata->sock;
		break;
	}

	// ディスクリプタ／イベント設定
	for( int i = 0; i < MAX_SERVER_THREAD_SOCKET; i++ ) {
		stFds[i].fd			= sock;
		stFds[i].events		= POLLIN | POLLERR;
		stFds[i].revents	= 0;
	}

	while( 1 ) {

		// poll
		for( int i = 0; i < MAX_SERVER_THREAD_SOCKET; i++ ) {

			rpoll = poll(stFds, MAX_SERVER_THREAD_SOCKET, POLL_WAIT_TIME);

			switch(rpoll){
			case -1:	// poll error
				break;

			case 0:		// poll timeout
				// send(pthdata->sock, send_buf, sizeof(send_buf), 0);
				// printf("Server send[%s]\n", send_buf);
				break;

			default:
				if( 0 != ( POLLIN & stFds[i].revents ) ) {
					/* クライアントからデータを受信 */
					memset(recv_buf, 0, sizeof(recv_buf));
					recv_size = recv(sock, recv_buf, MAX_BUF, 0);
					printf("(%lu)Server recv[%s] recv_size=%d\n", pthdata->th, recv_buf, recv_size);

					if( 0 == recv_size ){
						fprintf(stderr, "recv_size is 0 rpoll=%d, revents=0x%x\n", rpoll, stFds[i].revents);
						exit(EXIT_FAILURE);
					}
				}
				break;
			}
		}
	}

	printf("(%lu)ServerThread end\n", pthdata->th);

	return (void *) NULL;
}

int main (void)
{
	int i = 0;
	int rtn = 0;
	int sock = 0;
	int rpoll = 0;
	int yes = 1;
	int sock0[MAX_LISTEN_SOCKET] = { 0 };
	socklen_t len = 0;
	struct thdata *thdata = NULL;
	struct sockaddr_in addr = { 0 };
	struct sockaddr_in client = { 0 };
	struct pollfd stFds[MAX_LISTEN_SOCKET] = { 0 };
    struct sigaction act = { 0 };

    // シグナル(SIGPIPE) 受信時に handler() を実行するように設定。
    act.sa_handler = handler;
    sigaction(SIGPIPE, &act, NULL);

	/* Threadデータ初期化 */
	thdata = calloc(sizeof(struct thdata), MAX_SERVER_THREAD);
	if(thdata == NULL) {
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	// Thread生成
	for(i = 0; i < MAX_SERVER_THREAD; i++) {
        rtn = pthread_create(&thdata[i].th, NULL, ServerThread, (void *) (&thdata[i]));
		if (rtn != 0) {
			fprintf(stderr, "pthread_create() #%0d failed for %d.", i, rtn);
			exit(EXIT_FAILURE);
		}
    }

	for( int i = 0; i < MAX_LISTEN_SOCKET; i++ ) {

		// Socket生成
		sock0[i] = socket(AF_INET, SOCK_STREAM, 0);
		if( sock0 < 0 ){
			perror("socket");
			return 1;
		}

		// ローカルアドレスの再利用
		setsockopt(sock0[i], SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

		// bind
		addr.sin_family = AF_INET;
		addr.sin_port = htons(LISTEN_PORT+i);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(sock0[i], (struct sockaddr *)&addr, sizeof(addr)) != 0) {
			perror("bind");
			return 1;
		}

		// Clientからのconnet()待ち受け開始（connetをキューイングする）
		// MAX_LISTEN_CONNECTはキューの数
		if (listen(sock0[i], MAX_LISTEN_CONNECT) != 0) {
			perror("listen");
			return 1;
		}

	}

	// ディスクリプタ／イベント設定
	for( int i = 0; i < MAX_LISTEN_SOCKET; i++ ) {
		stFds[i].fd			= sock0[i];
		stFds[i].events		= POLLIN | POLLERR;
		stFds[i].revents	= 0;
	}

	while( 1 ) {

		// poll
		for( int i = 0; i < MAX_LISTEN_SOCKET; i++ ) {

			rpoll = poll(stFds, MAX_LISTEN_SOCKET, POLL_WAIT_TIME);

			switch(rpoll){
			case -1:	// poll error
				break;

			case 0:		// poll timeout
				printf("poll timeout...\n");
				break;

			default:

				if( 0 != ( POLLIN & stFds[i].revents ) ) {
					// Clientからのconnect()受付
					// connect()があるまで待たされる
					len = sizeof(client);
					sock = accept(sock0[i], (struct sockaddr *)&client, &len);
					if (sock < 0) {
						perror("accept");
						break;
					}
					thdata[i].sock = sock;
					printf("Connected from %s port=%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
					printf("sock [%d]\n", thdata[i].sock);
				}
				break;
			}
		}
	}

	for( int i = 0; i < MAX_LISTEN_SOCKET; i++ ) {
		close(sock0[i]);
	}

	/* join */
	for(i = 0; i < MAX_SERVER_THREAD; i++) {
		pthread_join(thdata[i].th, NULL);
	}

	printf("Server main end\n");

	free(thdata);

	exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>	// for pthread_create, pthread_join
#include <unistd.h>		// for close, sleep
#include <sys/socket.h>	// for socket
#include <arpa/inet.h>	// for inet_ntoa
#include <poll.h>		// for poll
#include <signal.h>		// for sigaction

#define MAX_SERVER_THREAD	1
#define MAX_SOCKET_NUM		1		// サーバ最大socket数(ディスクリプタ数)
#define	POLL_WAIT_TIME		3000	// poll待ち付けタイムアウト(ms)
#define	PORT_NUM			12345	// 待ち受けポート番号
#define	MAX_CONNECT			5		// サーバ最大接続受付数
#define	MAX_BUF				256		// 送受信バッファサイズ

// スレッドに渡されるデータ
struct thdata {
	pthread_t	th;
	int			sock;
};

static void handler(int signo)
{
	/* 
		* 本来ハンドラ内では、非同期シグナルセーフな関数を使用するべきですが、
		* ここでは、そうでない printf()、exit() などの関数を使用しています。
		* 非同期シグナルセーフについては $ man 7 signal をご参照ください。
		*/
	printf(" ... Caught the SIGINT (%d)\n", signo);
	exit(EXIT_SUCCESS);
}

void *ServerThread(void *thdata)
{
	int sock = 0;
	int recv_size = 0;
	char recv_buf[MAX_BUF] = { 0 };
	char send_buf[MAX_BUF] = { 0 };
	struct thdata	*pthdata = NULL;

	// スレッドに渡されるデータ
	pthdata = (struct thdata *)thdata;

	// 送信データ
	strncpy( send_buf, "HELLO", sizeof(send_buf) );

	while( 1 ) {

		if( 0 == pthdata->sock ) {
			printf("Server wait socket initialize...\n");
			sleep(1);	// 1秒
			continue;
		}

		sock = pthdata->sock;

		send(pthdata->sock, send_buf, sizeof(send_buf), 0);
		printf("Server send[%s]\n", send_buf);
		recv_size = recv(sock, recv_buf, MAX_BUF, 0);
		printf("Server recv[%s] recv_size=%d\n", recv_buf, recv_size);
	}

	printf("ServerThread end\n");

	return (void *) NULL;
}

int main (void)
{
	int                 rtn, i;
	struct thdata       *thdata;
	int					sock0[MAX_SOCKET_NUM];
	int					sock;
	socklen_t			len;
	int					yes = 1;
	struct				sockaddr_in addr;
	struct				sockaddr_in client;
	struct pollfd		stFds[MAX_SOCKET_NUM];
	int					rpoll;
    struct sigaction	act;

    // シグナル(SIGPIPE) 受信時に handler() を実行するように設定。
    memset(&act, 0, sizeof act);
    act.sa_handler = handler;
    sigaction(SIGPIPE, &act, NULL);

	/* initialize thread data */
	thdata = calloc(sizeof(struct thdata), MAX_SERVER_THREAD);
	if (thdata == NULL) {
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	// Thread生成
	for (i = 0; i < MAX_SERVER_THREAD; i++) {
        rtn = pthread_create(&thdata[i].th, NULL, ServerThread, (void *) (&thdata[i]));
		if (rtn != 0) {
			fprintf(stderr, "pthread_create() #%0d failed for %d.", i, rtn);
			exit(EXIT_FAILURE);
		}
    }

	for( int i = 0; i < MAX_SOCKET_NUM; i++ ) {

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
		addr.sin_port = htons(PORT_NUM+i);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(sock0[i], (struct sockaddr *)&addr, sizeof(addr)) != 0) {
			perror("bind");
			return 1;
		}

		// Clientからのconnet()待ち受け開始（connetをキューイングする）
		// MAX_CONNECTはキューの数
		if (listen(sock0[i], MAX_CONNECT) != 0) {
			perror("listen");
			return 1;
		}

	}

	// ディスクリプタ／イベント設定
	for( int i = 0; i < MAX_SOCKET_NUM; i++ ) {
		stFds[i].fd			= sock0[i];
		stFds[i].events		= POLLIN | POLLERR;
		stFds[i].revents	= 0;
	}

	while( 1 ) {

		// poll
		for( int i = 0; i < MAX_SOCKET_NUM; i++ ) {

			rpoll = poll(stFds, MAX_SOCKET_NUM, POLL_WAIT_TIME);

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
					thdata->sock = sock;
					printf("Connected from %s\n", inet_ntoa(client.sin_addr));
					printf("sock [%d]\n", thdata->sock);
				}
				break;
			}
		}
	}

	for( int i = 0; i < MAX_SOCKET_NUM; i++ ) {
		close(sock0[i]);
	}

	/* join */
	for (i = 0; i < MAX_SERVER_THREAD; i++) {
		pthread_join(thdata[i].th, NULL);
	}

	free(thdata);

	exit(EXIT_SUCCESS);
}

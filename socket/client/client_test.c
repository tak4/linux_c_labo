#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>	// for pthread_create, pthread_join
#include <unistd.h>		// for close, sleep
#include <sys/socket.h>	// for socket
#include <arpa/inet.h>	// for inet_ntoa
#include <poll.h>		// for poll

#define SERVER_IP_ADDRESS	"192.168.1.10"
#define MAX_CLIENT_THREAD  			1		// クライアントスレッド数
#define MAX_CLIENT_THREAD_SOCKET	1		// クライアントスレッドSocket数
#define	POLL_WAIT_TIME				3000	// poll待ち付けタイムアウト(ms)
#define	MAX_BUF						256		// 送受信バッファサイズ


// スレッドに渡されるデータ
struct thdata {
	pthread_t th;
};

int port_no = 0;
char send_word[MAX_BUF] = { 0 };

void *ClientThread()
{
	struct sockaddr_in server;
	int sock = 0; 
	int	rpoll = 0;
	int recv_size = 0;
	char recv_buf[MAX_BUF] = { 0 };
	char send_buf[MAX_BUF] = { 0 };
	struct pollfd stFds[MAX_CLIENT_THREAD_SOCKET];
	struct sockaddr_in addr = { 0 };

	// 送信データ
	strncpy( send_buf, send_word, sizeof(send_buf) );

	// Socket生成
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// bind
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	// addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_addr.s_addr = inet_addr("192.168.1.12");

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		perror("bind");
		return NULL;
	}

	// ディスクリプタ／イベント設定
	for( int i = 0; i < MAX_CLIENT_THREAD_SOCKET; i++ ) {
		stFds[i].fd			= sock;
		stFds[i].events		= POLLIN | POLLERR;
		stFds[i].revents	= 0;
	}

	/* 接続先指定用構造体の準備 */
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

	/* サーバに接続 */
	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0) {
		perror("connect");
		return NULL;
	}

	while( 1 ){
		// poll
		for( int i = 0; i < MAX_CLIENT_THREAD_SOCKET; i++ ) {

			rpoll = poll(stFds, MAX_CLIENT_THREAD_SOCKET, POLL_WAIT_TIME);

			switch(rpoll){
			case -1:	// poll error
				break;

			case 0:		// poll timeout
				send(sock, send_buf, sizeof(send_buf), 0);
				printf("Client send[%s]\n", send_buf);
				break;

			default:
				if( 0 != ( POLLIN & stFds[i].revents ) ) {
					/* サーバからデータを受信 */
					memset(recv_buf, 0, sizeof(recv_buf));
					recv_size = recv(sock, recv_buf, MAX_BUF, 0);
					printf("Client recv[%s] recv_size=%d\n", recv_buf, recv_size);

					if( 0 == recv_size ){
						fprintf(stderr, "recv_size is 0 rpoll=%d, revents=0x%x\n", rpoll, stFds[i].revents);
						exit(EXIT_FAILURE);
					}
				}
				break;
			}
		}
	}

	close(sock);

	/* done */
	return (void *) NULL;
}

int main ( int argc, char *argv[] )
{
	int i = 0;
	int rtn = 0;
	struct thdata *thdata = NULL;

	if( 3 != argc ){
		printf("Usage : %s [port no] [send word]\n", argv[0]);
		return -1;
	}

	// port番号設定
	port_no = atoi(argv[1]);
	strncpy(send_word, argv[2],sizeof(send_word));

	/* Threadデータ初期化 */
	thdata = calloc(sizeof(struct thdata), MAX_CLIENT_THREAD);
	if (thdata == NULL) {
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	// Thread生成
	for (i = 0; i < MAX_CLIENT_THREAD; i++) {
        rtn = pthread_create(&thdata[i].th, NULL, ClientThread, (void *) (&thdata[i]));
		if (rtn != 0) {
			fprintf(stderr, "pthread_create() #%0d failed for %d.", i, rtn);
			exit(EXIT_FAILURE);
		}
    }

	/* join */
	for (i = 0; i < MAX_CLIENT_THREAD; i++) {
		pthread_join(thdata[i].th, NULL);
	}

	printf("Client main end\n");

	free(thdata);
	exit(EXIT_SUCCESS);

}

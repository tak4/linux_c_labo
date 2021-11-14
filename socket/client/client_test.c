#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>	// for pthread_create, pthread_join
#include <unistd.h>		// for close, sleep
#include <sys/socket.h>	// for socket
#include <arpa/inet.h>	// for inet_ntoa

#define SERVER_IP_ADDRESS	"192.168.1.10"
#define MAX_CLIENT_THREAD   1
#define	PORT_NUM			12345	// 待ち受けポート番号
#define	MAX_BUF				256		// 送受信バッファサイズ


// スレッドに渡されるデータ
struct thdata {
	pthread_t           th;
};

void *ClientThread()
{
	struct sockaddr_in server;
	int sock = 0; 
	int recv_size = 0;
	char recv_buf[MAX_BUF] = { 0 };
	char send_buf[MAX_BUF] = { 0 };

	// 送信データ
	strncpy( send_buf, "HELLO", sizeof(send_buf) );

	// Socket生成
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// // ローカルアドレスの再利用可否
	// setcoketopt
	// SOL_SOCKET, SO_REUSEADDRESS

	// // Keep-Alive MSGの有効/無効状態
	// SOL_SOCKET, SO_KEEPALIVE

	// // 受信バッファサイズ
	// SOL_SOCKET, SO_RCVBUF

	// // 送信バッファサイズ
	// SOL_SOCKET, SO_SNDBUF

	// // Nagleアルゴリズムの有効/無効状態
	// IPPROTO_IP, TCP_NODELAY

	// // Socket I/O制御オプション設定
	// ioctrl(socket, FIONBIO, &retval)

	// connect

	/* 接続先指定用構造体の準備 */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_NUM);
	server.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

	/* サーバに接続 */
	connect(sock, (struct sockaddr *)&server, sizeof(server));

	/* サーバからデータを受信 */
	memset(recv_buf, 0, sizeof(recv_buf));
	recv_size = recv(sock, recv_buf, sizeof(recv_buf), 0);
	printf("Client recv[%s] recv_size=%d\n", recv_buf, recv_size);
	send(sock, send_buf, sizeof(send_buf), 0);
	printf("Client send[%s]\n", send_buf);

	while( 1 ){
		printf("ClientThead block...\n");
		sleep(1);
	}

	close(sock);

	/* done */
	return (void *) NULL;
}

int main (void)
{
	int                 rtn, i;
	struct thdata       *thdata;

	/* initialize thread data */
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

	free(thdata);
	exit(EXIT_SUCCESS);

}

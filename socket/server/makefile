#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:		server_test

server_test:	server_test.o
			$(CC) $(CFLAG) server_test.o -o server_test -lpthread

server_test.o:	server_test.c
			$(CC) $(CFLAG) -c server_test.c

clean:
	@\rm -f *.o

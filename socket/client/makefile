#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:		client_test

client_test:	client_test.o
			$(CC) $(CFLAG) client_test.o -o client_test -lpthread

client_test.o:	client_test.c
			$(CC) $(CFLAG) -c client_test.c

clean:
	@\rm -f *.o

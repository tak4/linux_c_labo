#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:			thread_sample
thread_sample:	thread_sample.o
			$(CC) $(CFLAG) thread_sample.o -o thread_sample -lpthread

thread_sample.o:	thread_sample.c
			$(CC) $(CFLAG) -c thread_sample.c

.PHONY : clean
clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


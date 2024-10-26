#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:			synchronized_method
synchronized_method:	synchronized_method.o
			$(CC) $(CFLAG) synchronized_method.o -o synchronized_method -lpthread

synchronized_method.o:	synchronized_method.cpp
			$(CC) $(CFLAG) -c synchronized_method.cpp

.PHONY : clean
clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


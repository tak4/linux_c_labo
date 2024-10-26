#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:			backtrace
backtrace:	backtrace.o
			$(CC) $(CFLAG) backtrace.o -o backtrace

backtrace.o:	backtrace.cpp
			$(CC) $(CFLAG) -c backtrace.cpp

.PHONY : clean
clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


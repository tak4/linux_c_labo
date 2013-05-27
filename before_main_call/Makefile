#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all:	before_main_call

before_main_call:	main.o
			$(CC) $(CFLAG) main.o -o before_main_call

main.o:	main.cpp
			$(CC) $(CFLAG) -c main.cpp

.PHONY : clean
clean:
# @\はコンソールに表示しない為の指示
	@rm -f *.o


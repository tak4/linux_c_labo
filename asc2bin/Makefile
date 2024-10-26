#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall

all	:			asc2bin
asc2bin:	asc2bin.o
			$(CC) $(CFLAG) asc2bin.o -o asc2bin

asc2bin.o:	asc2bin.cpp
			$(CC) $(CFLAG) -c asc2bin.cpp

clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o

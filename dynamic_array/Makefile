#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall

all	:		dynamic_array
dynamic_array:	dynamic_array.o
			$(CC) $(CFLAG) dynamic_array.o -o dynamic_array

dynamic_array.o:	dynamic_array.cpp
			$(CC) $(CFLAG) -c dynamic_array.cpp

clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o

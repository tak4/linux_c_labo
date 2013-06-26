#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall -fpermissive

all	:			reflection
reflection:	reflection.o
			$(CC) $(CFLAG) reflection.o -o reflection

reflection.o:	reflection.cpp
			$(CC) $(CFLAG) -c reflection.cpp

clean:
	@\rm -f *.o


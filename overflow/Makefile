#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:			overflow
overflow:	main.o _strtol.o
			$(CC) $(CFLAG) main.o _strtol.o -o overflow

main.o:	main.cpp
			$(CC) $(CFLAG) -c main.cpp

_strtol.o:	_strtol.h _strtol.cpp
			$(CC) $(CFLAG) -c _strtol.cpp
	
clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


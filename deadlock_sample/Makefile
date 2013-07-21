#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:			astall
astall:	astall.c
			$(CC) $(CFLAG) astall.c -o astall -lpthread

.PHONY : clean
clean:
# @\はコンソールに表示しない為の指示
	@rm -f *.o


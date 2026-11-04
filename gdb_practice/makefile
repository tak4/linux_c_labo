#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:		gdb_practice

gdb_practice:	gdb_practice.o
			$(CC) $(CFLAG) gdb_practice.o -o gdb_practice

gdb_practice.o:	gdb_practice.c
			$(CC) $(CFLAG) -c gdb_practice.c

clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o

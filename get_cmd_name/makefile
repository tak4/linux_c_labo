#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall

all	:		get_cmd_name

get_cmd_name:	get_cmd_name.o
			$(CC) $(CFLAG) get_cmd_name.o -o get_cmd_name -lpthread

get_cmd_name.o:	get_cmd_name.c
			$(CC) $(CFLAG) -c get_cmd_name.c

clean:
	@\rm -f *.o

#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall

all	:			checkAlign
checkAlign:	checkAlign.o
			$(CC) $(CFLAG) checkAlign.o -o checkAlign

checkAlign.o:	checkAlign.cpp
			$(CC) $(CFLAG) -c checkAlign.cpp

.PHONY : clean
clean:
# @\はコンソルに表示しない為の指示
	@rm -f *.o



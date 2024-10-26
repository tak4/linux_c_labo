#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall

all	:			override_test
override_test:	override_test.o
			$(CC) $(CFLAG) override_test.o -o override_test

override_test.o:	override_test.cpp
			$(CC) $(CFLAG) -c override_test.cpp

.PHONY : clean
clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=g++
CFLAG=-g -Wall -I/home/takashi/develop/flatbuffers/include

all	:			serialize deserialize
serialize:	serialize.o
			$(CC) $(CFLAG) serialize.o -o serialize

deserialize:	deserialize.o
			$(CC) $(CFLAG) deserialize.o -o deserialize

serialize.o:	serialize.cpp
			$(CC) $(CFLAG) -c serialize.cpp

deserialize.o:	deserialize.cpp
			$(CC) $(CFLAG) -c deserialize.cpp

.PHONY : clean
clean:
# @\はコンソルに表示しない為の指示
	@rm -f *.o


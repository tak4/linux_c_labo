#ターゲット名:	依存関係ファイル
#				コマンド
#ターゲット名は gcc -o の代わり

CC=gcc
CFLAG=-g -Wall
#OBJGROUP=main.o libTest.o libTestShared.so.1.0.1

all	:			testSharedlib
testSharedlib:	main.o libTest.o libTestShared.so.1.0.1
					$(CC) $(CFLAG) -Wl,-rpath,. -L. -lTestShared main.o libTest.o -lpthread -o testSharedlib

main.o:	main.cpp
			$(CC) $(CFLAG) -c main.cpp

libTest.o:	libTest.cpp libTest.h
			$(CC) $(CFLAG) -c libTest.cpp

libTestShared.o:	libTestShared.cpp libTestShared.h
					$(CC) $(CFLAG) -fPIC -c libTestShared.cpp

libTestShared.so.1.0.1:	libTestShared.o
							$(CC) $(CFLAG) -shared -Wl,-soname,libTestShared.so.1 libTestShared.o -lpthread -o libTestShared.so.1.0.1


clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o


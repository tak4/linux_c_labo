CC=gcc
CFLAG=-g -Wall  -I./inc_first -I./inc_second

all	:		include_test

include_test:	include_test.o
			$(CC) $(CFLAG) include_test.o -o include_test -lpthread

include_test.o:	include_test.c
			$(CC) $(CFLAG) -c include_test.c

clean:
# @はコンソールに表示しない為の指示
	@rm -f *.o

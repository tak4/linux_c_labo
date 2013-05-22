#include <stdio.h>
#include "_strtol.h"

int main()
{
	printf("%d,%d\n", sizeof(short int), sizeof(long));

	short int data = 0L;
	int overflow = 0;

	char dataStr[32] = { "-3560" };
	data = _strtoi( dataStr, &overflow );
	printf("data=%d overflow=%d\n", data, overflow);
}

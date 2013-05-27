#include <stdio.h>

//
// __attribute__((constructor)) を利用する方法
// gcc 環境のみ利用可能
//
__attribute__((constructor))
void foo()
{
	printf("hello, before main(1)\n");
}

//
// C++ structのコンストラクタを利用する方法
// C++環境なら移植性がある
//
void foo2()
{
	printf("hello, before main(2)\n");
}
namespace { 
	struct foo_caller { 
		foo_caller() 
		{
			foo2();
		} 
	} caller; 
}

int main()
{
	printf("hello, world\n");
	return 0;
}


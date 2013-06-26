#include <stdio.h>
#include <typeinfo>
#include <cxxabi.h>
#include "reflection.h"

using namespace std;

char* demangle(const char *demangle)
{
	int status;
	return abi::__cxa_demangle(demangle, 0, 0, &status);
}

int main()
{
	Super *pSuper;

	pSuper = new Sub1();
	printf("%s\n", typeid(*pSuper).name());
	printf("%s\n", demangle(typeid(*pSuper).name()));
	delete pSuper;

	pSuper = new Sub2();
	printf("%s\n", typeid(*pSuper).name());
	printf("%s\n", demangle(typeid(*pSuper).name()));
	delete pSuper;

	pSuper = new SubA();
	printf("%s\n", typeid(*pSuper).name());
	printf("%s\n", demangle(typeid(*pSuper).name()));
	delete pSuper;
	
	return 0;
}

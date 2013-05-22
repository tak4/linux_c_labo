#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

/* Obtain a backtrace and print it to stdout. */
//
// print_trace() or print_trace2() どちらかを使用することでバックトレース出力可能
//
void print_trace (void)
{
	void *array[10];
	size_t size;
	char **strings;
	size_t i;

	size = backtrace (array, 10);
	strings = backtrace_symbols (array, size);

	printf ("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf ("%s\n", strings[i]);

	free (strings);
}

void print_trace2 (void)
{
	void *array[10];
	size_t size;
	size = backtrace (array, 10);
	backtrace_symbols_fd (array, size, 1);
}

/* A dummy function to make the backtrace more interesting. */
void dummy_function2 (void)
{
	print_trace ();
	printf("-----------------------\n");
	print_trace2 ();
}

void dummy_function (void)
{
	dummy_function2 ();
}

int main (void)
{
	dummy_function ();
	return 0;
}

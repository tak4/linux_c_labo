#include <stdio.h>
#include <pthread.h>

#include "libTest.h"
#include "libTestShared.h"

void *main_loop( void *param )
{
	while( 1 )
	{
		libTest1();
		libTestShared();
	}

	return NULL;
}

void *TaskA( void *param )
{
	printf("TaskA\n");
	libTest1();
	libTestShared();

	return NULL;
}

void *TaskB( void *param )
{
	printf("TaskB\n");
	libTest1();
	libTestShared();

	return NULL;
}

void *TaskC( void *param )
{
	printf("TaskC\n");
	libTest1();
	libTestShared();

	return NULL;
}

int main()
{
	int rtn1, rtn2, rtn3, rtn4;
	pthread_t th[4] = { 0 };

	rtn1 = pthread_create(&th[0], NULL, main_loop, NULL);
//	rtn2 = pthread_create(&th[1], NULL, TaskA, NULL);
//	rtn3 = pthread_create(&th[2], NULL, TaskB, NULL);
//	rtn4 = pthread_create(&th[3], NULL, TaskC, NULL);

	// 全スレッドが終了するまでmain関数を終了させない 一応・・・
	pthread_join(th[0], NULL);
//	pthread_join(th[1], NULL);
//	pthread_join(th[2], NULL);
//	pthread_join(th[3], NULL);

	return 0;
}



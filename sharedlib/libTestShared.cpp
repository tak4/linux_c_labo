#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include "libTestShared.h"

struct thdata {
	char                letter;
	pthread_t           th;
	sem_t               sync;
	sem_t               start;
};

void *thread_function(void *pthdata)
{
	struct thdata       *priv = (struct thdata *)pthdata;

	/* sync */
	sem_post(&priv->sync);
	sem_wait(&priv->start);

	/* write my letter */
	putchar(priv->letter);

	/* sync */
	sem_post(&priv->sync);

	/* done */
	return (void *) NULL;
}

int libTestShared()
{
	printf(" libTestShared() start\n");
	usleep(10000);
	printf(" libTestShared() end\n");
	return 0;
}

void threadPutChar()
{
	int						rtn;
	unsigned int			i;
	struct thdata			*pthdata;
	char					hello[128] = "Hello World!\n";

	/* initialize thread data */
	pthdata = (struct thdata *)calloc(sizeof(struct thdata), strlen(hello));
	if (pthdata == NULL)
	{
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	// 1文字 - 1スレッド起動
	for (i = 0; i < strlen(hello); i++)
	{
		pthdata[i].letter = hello[i];
		// セマフォ初期化
		// int sem_init(sem_t *sem, int pshared, unsigned int value); 
		//		sem			: セマフォID
		//		pshared	: 0 スレッド間共有　0以外 プロセス間共有
		//		value		: セマフォ初期値　
		sem_init(&pthdata[i].sync, 0, 0);
		sem_init(&pthdata[i].start, 0, 0);

		// スレッド起動
		// int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
		// 		thread			: スレッドID
		//		attr			: 生成するスレッドに付加する属性(詳細不明)
		//		start_routine	: タスクエントリポイント
		//		arg				: タスクエントリポイントへ渡す引数
		rtn = pthread_create(&pthdata[i].th, NULL, thread_function, (void *) (&pthdata[i]));
		if (rtn != 0)
		{
			fprintf(stderr, "pthread_create() #%0d failed for %d.", i, rtn);
			exit(EXIT_FAILURE);
		}
	}


	/* synchronization */
	// 文字出力スレッド待ち合わせ
	for (i = 0; i < strlen(hello); i++)
	{
		sem_wait(&pthdata[i].sync);
	}

	/* let thread write his letter */
	// H -> e -> l -> l -> o の順にスレッドを動かす
	for (i = 0; i < strlen(hello); i++)
	{
		sem_post(&pthdata[i].start);
		sem_wait(&pthdata[i].sync);
	}

	/* join */
	for (i = 0; i < strlen(hello); i++)
	{
		pthread_join(pthdata[i].th, NULL);
		sem_destroy(&pthdata[i].sync);
		sem_destroy(&pthdata[i].start);
	}

	free(pthdata);
}


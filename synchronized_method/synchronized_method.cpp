#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

struct thdata {
	pthread_t           th;
};

void need_to_sync();

void *thread_function(void *thdata)
{
	struct thdata       *priv = (struct thdata *)thdata;

	printf("Hello!! (%lx)\n", priv->th);
	need_to_sync();

	return (void *) NULL;
}

const int thread_num = 2;
int main (void)
{

	int                 rtn, i;
	struct thdata       *pthdata;

	/* initialize thread data */
	pthdata = (thdata *)calloc(sizeof(struct thdata), thread_num);
	if (pthdata == NULL) {
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < thread_num; i++) {
		rtn = pthread_create(&pthdata[i].th, NULL, thread_function, (void *) (&pthdata[i]));
		if (rtn != 0) {
			fprintf(stderr, "pthread_create() #%0d failed for %d.", i, rtn);
			exit(EXIT_FAILURE);
		}
	}

	/* join */
	for (i = 0; i < thread_num; i++) {
		pthread_join(pthdata[i].th, NULL);
	}

	free(pthdata);
	exit(EXIT_SUCCESS);
}

template<typename T>
class scoped_lock_ /* private boost::noncopyable */ {
	T& m_;
public:
	explicit scoped_lock_(T& m)
	 : m_(m)
	{
		m_.lock();
	}
	~scoped_lock_() throw()
	{
		m_.unlock();
	}
};

#define STATIC_MUTEX_INIT {PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP};
struct static_mutex {
	pthread_mutex_t m_;
	void lock() {
		pthread_mutex_lock(&m_);
	}
	void unlock() {
		pthread_mutex_unlock(&m_);
	}
	typedef scoped_lock_<static_mutex> scoped_lock;
};

namespace { static_mutex m = STATIC_MUTEX_INIT; }
void need_to_sync() {
	static_mutex::scoped_lock lk(m);
}


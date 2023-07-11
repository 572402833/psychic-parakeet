#include "../include/head.h"

void thread_init()
{
	int res;
	// 定义两个表示线程的变量（标识符）
	pthread_t Thread;
	// 创建 myThread1 线程
	res = pthread_create(&Thread, NULL, thread_start, NULL);
	if (res != 0)
	{
		printf("线程创建失败");
		return;
	}
}

void *thread_start(void *arg)
{
	while (1)
		get_xy();
}
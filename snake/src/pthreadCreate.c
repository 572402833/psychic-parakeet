#include "../include/head.h"

void thread_init()
{
	int res;
	// ����������ʾ�̵߳ı�������ʶ����
	pthread_t Thread;
	// ���� myThread1 �߳�
	res = pthread_create(&Thread, NULL, thread_start, NULL);
	if (res != 0)
	{
		printf("�̴߳���ʧ��");
		return;
	}
}

void *thread_start(void *arg)
{
	while (1)
		get_xy();
}
/*
 * =====================================================================================
 *
 *       Filename:  thread_cancel.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 08:17:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void* arg);

int main()
{
	int res;
	pthread_t a_thread;
	void* result;

	res = pthread_create(&a_thread, NULL, thread_func, NULL);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	sleep(5);

	printf("Canceling thread ... \n");
	res = pthread_cancel(a_thread);
	if(res != 0)
	{
		perror("Thread cancelation failed");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for thread to finish ... \n");
	res = pthread_join(a_thread, &result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	int i, res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if(res != 0)
	{
		perror("Thread pthread_setcancelstate failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	if(res != 0)
	{
		perror("Thread pthread_setcanceltype failed");
		exit(EXIT_FAILURE);
	}
	printf("thread function is running\n");
	for(i = 0; i < 10; i++)
	{
		printf("Thread is still running (%d) ... \n", i);
		sleep(1);
	}
	pthread_exit(0);
}

/*
 * =====================================================================================
 *
 *       Filename:  thread_lots.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 08:42:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

void* thread_func(void* arg);

int main()
{
	pthread_t threads[NUM_THREADS];
	void* result;
	int res;
	int idx;

	for(idx = 0; idx < NUM_THREADS; idx++)
	{
		res = pthread_create(&(threads[idx]), NULL, thread_func, (void*)idx);
		if(res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
//		sleep(1);
	}

	printf("Waiting for threads to finish ... \n");

	for(idx = NUM_THREADS-1; idx >= 0; idx--)
	{
		res = pthread_join(threads[idx], &result);
		if(res == 0)
		{
			printf("Picked up a thread\n");
		}
		else
		{
			perror("pthread_join failed");
		}
	}
	printf("All done\n");
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	int idx = (int)arg;
	int rand_num;

	printf("thread_func is running. Argument was %d\n", idx);
	rand_num = 1 + (9.0*rand()/(RAND_MAX+1.0));
	sleep(rand_num);
	printf("Bye from %d\n", idx);
	pthread_exit(NULL);
}









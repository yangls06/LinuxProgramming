/*
 * =====================================================================================
 *
 *       Filename:  thread_simu.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/08/2012 11:40:13 AM
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

char msg[] = "Hello World!";
int run_now = 1;
void* thread_func(void* arg);

int main()
{
	int res;
	pthread_t a_thread;
	void* result;
	int print_count1 = 0;

	res = pthread_create(&a_thread, NULL, thread_func, (void*)msg);
	if(res != 0)
	{
		perror("Thread Creation failed");
		exit(EXIT_FAILURE);
	}

	while(print_count1++ < 10)
	{
		if(run_now == 1)
		{
			printf("1");
			run_now = 2;
		}
		else
		{
			sleep(1);
		}
	}

	printf("\nWaiting for thread to finish ... \n");
	res = pthread_join(a_thread, &result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined!\n");
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	int print_count2 = 1;
	while(print_count2++ < 10)
	{
		if(run_now == 2)
		{
			printf("2");
			run_now = 1;
		}
		else
		{
			sleep(1);
		}
	}
}












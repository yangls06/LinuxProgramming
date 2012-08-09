/*
 * =====================================================================================
 *
 *       Filename:  thread_attr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/09/2012 04:40:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_func(void* arg);
char msg[] = "Hello World!";
int thread_finished = 0;

int main()
{
	int res;
	pthread_t a_thread;
	pthread_attr_t thread_attr;

	res = pthread_attr_init(&thread_attr);
	if(res != 0)
	{
		perror("Attribute creation failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if(res != 0)
	{
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, &thread_attr, thread_func, (void*)msg);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	(void)pthread_attr_destroy(&thread_attr);
	while(!thread_finished)
	{
		printf("Waiting for thread to say it's finished...\n");
		sleep(1);
	}

	printf("Other thread finished, bye!\n");
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	printf("thread_func is running. Argument was %s\n", (char*)arg);
	sleep(4);
	printf("Second thread setting finished flag, and exiting now\n");
	thread_finished = 1;
	pthread_exit(NULL);
}















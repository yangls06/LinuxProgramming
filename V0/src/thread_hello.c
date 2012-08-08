/*
 * =====================================================================================
 *
 *       Filename:  thread_hello.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/08/2012 11:01:36 AM
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
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void* arg);

char msg[] = "Hello World!";

int main()
{
	int res;
	pthread_t a_thread;
	void* result;

	res = pthread_create(&a_thread, NULL, thread_func, (void*)msg);
	if(res != 0) // creating thread failed
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for thread to finish ... \n");
	res = pthread_join(a_thread, &result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined, it returned %s\n", (char*)result);
	printf("Message in now %s\n", msg);
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	printf("thread_func is running. Argument was %s\n", (char*)arg);
	sleep(3);
	strcpy(msg, "Bye!");
	pthread_exit("Thank you for the CPU time");
}

















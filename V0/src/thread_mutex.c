/*
 * =====================================================================================
 *
 *       Filename:  thread_mutex.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/08/2012 03:02:17 PM
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
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void* thread_func(void* arg);
pthread_mutex_t mutex; /* protect both work_area and time_to_exit */

#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;

int main()
{
	int res;
	pthread_t a_thread;
	void* result;

	res = pthread_mutex_init(&mutex, NULL);
	if(res != 0)
	{
		perror("Mutex init failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, NULL, thread_func, NULL);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_lock(&mutex);
	printf("Input some text. Enter 'end' to finish\n");
	while(!time_to_exit)
	{
		fgets(work_area, WORK_SIZE, stdin);
		pthread_mutex_unlock(&mutex);
		while(1)
		{
			pthread_mutex_lock(&mutex);
			if(work_area[0] != '\0')
			{
				pthread_mutex_unlock(&mutex);
				sleep(1);
			}
			else
			{
				break;
			}
		}
	}
	pthread_mutex_unlock(&mutex);

	printf("\nWaiting for thread to finish ... \n");
	res = pthread_join(a_thread, &result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined\n");
	pthread_mutex_destroy(&mutex);
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	sleep(1);
	pthread_mutex_lock(&mutex);
	while(strncmp("end", work_area, 3) != 0)
	{
		printf("You input %d characters\n", strlen(work_area)-1);
		work_area[0] = '\0';
		pthread_mutex_unlock(&mutex);
		sleep(1);
		pthread_mutex_lock(&mutex);
		while(work_area[0] == '\0')
		{
			pthread_mutex_unlock(&mutex);
			sleep(1);
			pthread_mutex_lock(&mutex);
		}
	}
	time_to_exit = 1;
	work_area[0] = '\0';
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}














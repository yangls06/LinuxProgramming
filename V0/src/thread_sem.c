/*
 * =====================================================================================
 *
 *       Filename:  pthread_sem.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/08/2012 01:51:22 PM
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
#include <semaphore.h>
#include <string.h>

void* thread_func(void* arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main()
{
	int res;
	pthread_t a_thread;
	void* result;
	
	res = sem_init(&bin_sem, 0, 0);
	if(res != 0)
	{
		perror("Semaphore init failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, NULL, thread_func, NULL);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	printf("Input some text. Enter 'end' to finish\n");
	while(strncmp("end", work_area, 3) != 0)
	{
		fgets(work_area, WORK_SIZE, stdin);
		sem_post(&bin_sem);
	}

	printf("\nWaiting for thread to finish ... \n");
	res = pthread_join(a_thread, &result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_SUCCESS);
	}

	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	sem_wait(&bin_sem);
	while(strncmp("end", work_area, 3) != 0)
	{
		printf("You input %d characters\n", strlen(work_area)-1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}













/*
 * =====================================================================================
 *
 *       Filename:  ipc_shm_read.c
 *
 *    Description:  ipc using shared memory: write process
 *
 *        Version:  1.0
 *        Created:  08/14/2012 09:47:36 PM
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
#include <sys/shm.h>
#include "shm_com.h"

int main()
{
	int running = 1; 
	void* shm = NULL;
	int shm_id;
	struct shared_use_st* shared;
	char buffer[BUFSIZ];

	srand((unsigned int)getpid());
	shm_id = shmget((key_t)1234, sizeof(shared), 0666|IPC_CREAT);
	if(shm_id == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shm = shmat(shm_id, (void*)NULL, 0);
	if(shm == (void*)-1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Process %d: Memory attached at %X\n", (int)getpid(), (int)shm);
	shared = (struct shared_use_st*)shm;
	while(running)
	{
		while(shared->written == 1)
		{
			sleep(1);
			printf("waiting for client to read...\n");
		}
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		
		strncpy(shared->text, buffer, TXT_SZ);
		shared->written = 1;
		if(strncmp(shared->text, "end", 3) == 0)
		{
			running = 0;
		}
	}

	if(shmdt(shm) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}


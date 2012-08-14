/*
 * =====================================================================================
 *
 *       Filename:  ipc_sem.c
 *
 *    Description:  using semaphore for irc
 *
 *        Version:  1.0
 *        Created:  08/14/2012 08:43:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

//#include "semun.h"

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/*  union semun is defined by including <sys/sem.h> */
#else
/*  according to X/OPEN we have to define it ourselves */
union semun {		                
	int val;                  /*  value for SETVAL */					             
	struct semid_ds *buf;     /*  buffer for IPC_STAT, IPC_SET */								              
	unsigned short *array;    /*  array for GETALL, SETALL */											                                         /*  Linux specific part: */  
	struct seminfo *__buf;    /*  buffer for IPC_INFO */												          
};
#endif

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);

static int sem_id;

int main(int argc, char* argv[])
{
	int i;
	int pause_time;
	char op_char = 'O';

	srand((unsigned int)getpid());

	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

	if(argc > 1)
	{
		if(!set_semvalue())
		{
			fprintf(stderr, "Failed to initialize semaphore!\n");
			exit(EXIT_FAILURE);
		}
		op_char = 'X';
		sleep(2);
	}

	for(i = 0; i < 10; i++)
	{
		if(!semaphore_p())
		{
			exit(EXIT_FAILURE);
		}
		printf("%c", op_char);
		fflush(stdout);
		pause_time = rand()%3 + 1;
		sleep(pause_time);
		printf("%c", op_char);
		fflush(stdout);
		if(!semaphore_v())
		{
			exit(EXIT_FAILURE);
		}

		pause_time = rand()%2;
		sleep(pause_time);
	}

	printf("\nProcess %d finished\n", getpid());

	if(argc > 1)
	{
		sleep(10);
		del_semvalue();
	}

	exit(EXIT_SUCCESS);
}


static int set_semvalue(void)
{
	union semun sem_union;

	sem_union.val = 1;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1) return 0;
	return 1;
}

static void del_semvalue(void)
{
	union semun sem_union;
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
	{
		fprintf(stderr, "Failed to delete semaphore!\n");
	}
}

static int semaphore_p(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;  /* P */
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr, "semaphore_p failed\n");
		return 0;
	}
	return 1;
}

static int semaphore_v(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* V */
	sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr, "semaphore_v failed\n");
		return 0;
	}
	return 1;
}



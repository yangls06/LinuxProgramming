/*
 * =====================================================================================
 *
 *       Filename:  mq_rsv.c
 *
 *    Description:  IPC using message queue: receiving
 *
 *        Version:  1.0
 *        Created:  08/15/2012 08:22:20 PM
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
#include <errno.h>
#include <sys/msg.h>

struct msg_st {
	long type;
	char text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid;
	struct msg_st data;
	long receive = 0;

	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while (running)
	{
		if(msgrcv(msgid, (void*)&data, BUFSIZ, receive, 0) == -1)
		{
			fprintf(stderr, "msgrcv failed with error %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("You wrote: %s", data.text);
		if(strncmp(data.text, "end", 3) == 0)
		{
			running = 0;
		}
	}

	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}



















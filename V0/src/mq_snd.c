/*
 * =====================================================================================
 *
 *       Filename:  mq_snd.c
 *
 *    Description:  IPC using message queue: sending
 *
 *        Version:  1.0
 *        Created:  08/15/2012 08:38:56 PM
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

#define MAX_TXT 512

struct msg_st {
	long type;
	char text[MAX_TXT];
};

int main()
{
	int running = 1;
	struct msg_st data;
	int msgid;
	char buffer[BUFSIZ];

	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		data.type = 1;
		strcpy(data.text, buffer);
		if(msgsnd(msgid, (void*)&data, MAX_TXT, 0) == -1)
		{
			fprintf(stderr, "msgsnd failed with error %d\n", errno);
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, "end", 3) == 0)
		{
			running = 0;
		}
	}

	exit(EXIT_SUCCESS);
}


















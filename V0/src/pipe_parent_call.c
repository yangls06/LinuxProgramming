/*
 * =====================================================================================
 *
 *       Filename:  pipe_parent_call.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2012 05:18:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	const char data[] = "1234567890";
	int num;
	int pipe_files[2];
	int pid;
	char buffer[BUFSIZ+1];
	memset(buffer, '\0', sizeof(buffer));

	if(pipe(pipe_files) == 0)
	{
		pid = fork();
		
		if(pid < 0)
		{
			fprintf(stderr, "Fork failed!\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0) // in child process
		{
			sprintf(buffer, "%d", pipe_files[0]);
			(void)execl("pipe_child_call", "child call", buffer, (char*)0);
			exit(EXIT_SUCCESS);
		}

		if(pid > 0) // in parent process
		{
			num = write(pipe_files[1], data, strlen(data));
			printf("Wrote %d bytes in parent process.\n", num);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}


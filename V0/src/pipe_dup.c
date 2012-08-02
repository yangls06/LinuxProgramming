/*
 * =====================================================================================
 *
 *       Filename:  pipe_dup.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2012 10:53:01 PM
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
	int num;
	int pipe_files[2];
	pid_t pid;
	const char data[] = "1234567890";
	
	if(pipe(pipe_files) == 0)
	{
		pid = fork();
		
		if(pid < 0)
		{
			fprintf(stderr, "Fork failure!\n");
			exit(EXIT_SUCCESS);
		}

		if(pid == 0) // in child proces
		{
			close(0);
			dup(pipe_files[0]);
			close(pipe_files[0]);
			close(pipe_files[1]);
			printf("child process %d: \n", (int)getpid());
			execlp("od", "od", "-c", (char*)0);
			exit(EXIT_SUCCESS);
		}

		if(pid > 0) // in parent process
		{
			close(pipe_files[0]);
			num = write(pipe_files[1], data, strlen(data));
			close(pipe_files[1]);
			printf("parent progress %d - wrote %d bytes.\n", (int)getpid(), num);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}


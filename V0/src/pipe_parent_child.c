/*
 * =====================================================================================
 *
 *       Filename:  pipe_parent_child.c
 *
 *    Description:  pipe between parent process and child process
 *
 *        Version:  1.0
 *        Created:  08/01/2012 04:46:59 PM
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

int main()
{
	const char data[] = "1234567890";
	int num;
	int pipe_files[2];
	pid_t pid;
	
	char buffer[BUFSIZ+1];
	memset(buffer, '\0', sizeof(buffer));

	if(pipe(pipe_files) == 0)
	{
		pid = fork();
		if(pid == -1)
		{
			fprintf(stderr, "Fork Failed!\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0) // in child process
		{
			num = read(pipe_files[0], buffer, BUFSIZ);
			printf("Read %d bytes: %s\n", num, buffer);
			sleep(10);
			//exit(EXIT_SUCCESS);
		}

		if(pid > 0) // in parent process
		{
			num = write(pipe_files[1], data, strlen(data));
			printf("Wrote %d bytes\n", num);
			sleep(10);
			//exit(EXIT_SUCCESS);
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}


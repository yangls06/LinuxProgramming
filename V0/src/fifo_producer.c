/*
 * =====================================================================================
 *
 *       Filename:  fifo_producer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/07/2012 01:29:33 PM
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
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*1000)

int main()
{
	int pipe_fd;
	int res;
	int open_mode = O_WRONLY;
	int bytes_sent = 0;
	char buffer[BUFFER_SIZE+1];

	if(access(FIFO_NAME, F_OK) == -1)
	{
		res = mkfifo(FIFO_NAME, 0777);
		if(res != 0)
		{
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Producer process %d open FIFO O_WRONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("FIFO file %d opened\n", pipe_fd);

	if(pipe_fd != -1)
	{
		while(bytes_sent < TEN_MEG)
		{
			res = write(pipe_fd, buffer, BUFFER_SIZE);
			if(res == -1)
			{
				fprintf(stderr, "Write Error on pipe\n");
				exit(EXIT_FAILURE);
			}
			bytes_sent += res;
		}
		(void)close(pipe_fd);
	}
	else
	{
		fprintf(stderr, "Open FIFO failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Producer process %d finished\n", getpid());
	exit(EXIT_SUCCESS);
}


















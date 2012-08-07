/*
 * =====================================================================================
 *
 *       Filename:  fifo_create.c
 *
 *    Description:  create fifo with different kinds of flags
 *        Version:  1.0
 *        Created:  08/03/2012 05:08:45 PM
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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main(int argc, char* argv[])
{
	int res;
	int open_mode = 0;
	if (argc < 2) // has no params
	{
		fprintf(stderr, "Usage: %s <some combination of \
				O_RDONLY O_WRONLY O_NONBLOCK>\n", *argv);
		exit(EXIT_FAILURE);
	}

	argv++;
	if (strncmp(*argv, "O_RDONLY", 8) == 0) open_mode |= O_RDONLY;
	if (strncmp(*argv, "O_WRONLY", 8) == 0) open_mode |= O_WRONLY;
	if (strncmp(*argv, "O_NONBLOCK", 10) == 0) open_mode |= O_NONBLOCK;
	argv++;
	if (*argv)
	{
		if (strncmp(*argv, "O_RDONLY", 8) == 0) open_mode |= O_RDONLY;
		if (strncmp(*argv, "O_WRONLY", 8) == 0) open_mode |= O_WRONLY;
		if (strncmp(*argv, "O_NONBLOCK", 10) == 0) open_mode |= O_NONBLOCK;
	}

	if (access(FIFO_NAME, F_OK) == -1)
	{
		res = mkfifo(FIFO_NAME, 0777);
		if(res != 0)
		{
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d openning FIFO\n", getpid());
	res = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), res);
	sleep(5);
	if(res != -1) (void)close(res);
	printf("Process %d finished\n", getpid());
	exit(EXIT_SUCCESS);
}












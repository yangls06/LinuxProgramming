/*
 * =====================================================================================
 *
 *       Filename:  pipe_child_call.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2012 05:32:59 PM
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

int main(int argc, char* argv[])
{
	int num;
	char buffer[BUFSIZ+1];
	int fd;
	memset(buffer, '\0', sizeof(buffer));

	sscanf(argv[1], "%d", &fd);
	num = read(fd, buffer, BUFSIZ);
	
	printf("Read %d bytes in child process: %s\n", num, buffer);
	exit(EXIT_SUCCESS);
}


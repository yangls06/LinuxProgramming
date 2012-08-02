/*
 * =====================================================================================
 *
 *       Filename:  pipe_basic.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2012 04:32:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>   // for pipe func 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	const char data[] = "1234567890";
	int pipe_files[2];
	int num;

	char buffer[BUFSIZ+1];
	memset(buffer, '\0', sizeof(buffer));

	if(pipe(pipe_files) == 0)
	{
		num = write(pipe_files[1], data, strlen(data));
		printf("Wrote %d bytes\n", num);
		num = read(pipe_files[0], buffer, BUFSIZ);
		printf("Read %d bytes: %s\n", num, buffer);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

/*
 * =====================================================================================
 *
 *       Filename:  pipe_reads.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2012 03:25:31 PM
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
#include <string.h>

int main()
{
	FILE* pipe;
	char buffer[BUFSIZ+1];
	int num;
	memset(buffer, '\0', sizeof(buffer));

	pipe = popen("ps auxf", "r");
	if(pipe != NULL)
	{
		num = fread(buffer, sizeof(char), BUFSIZ, pipe);
		while(num > 0)
		{
			buffer[num] = '\0';
			printf("\n====Reading %d(BUFSIZ=%d)====: \n%s\n", num, BUFSIZ, buffer);
			num = fread(buffer, sizeof(char), BUFSIZ, pipe);
		}
		pclose(pipe);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}



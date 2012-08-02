/*
 * =====================================================================================
 *
 *       Filename:  popen_write.c
 *
 *    Description:  to test writing to a pipe
 *
 *        Version:  1.0
 *        Created:  08/01/2012 03:08:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lsyang
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>   // for popen
#include <stdlib.h>  // 
#include <unistd.h>  // for BUFSIZ
#include <string.h>  //

int main()
{
	FILE* pipe;
	char buffer[BUFSIZ+1];
	memset(buffer, '\0', sizeof(buffer));

	sprintf(buffer, "Once upon a time, there was an old ugly woman living in a ...\n");
	pipe = popen("od -c", "w");
	if(pipe != NULL)
	{
		fwrite(buffer, sizeof(char), strlen(buffer), pipe);
		pclose(pipe);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}


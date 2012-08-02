/*
 * =====================================================================================
 *
 *       Filename:  popen_test.c
 *
 *    Description:  To practise pipe using popen 
 *
 *        Version:  1.0
 *        Created:  08/01/2012 02:46:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lsyang
 *   Organization:  
 *
 * =====================================================================================
 */
/* WHERE popen STAY */
#include <stdio.h>
/* WHERE exit STAY*/
#include <stdlib.h>
/* WHERE BUFSIZ STAY */
#include <unistd.h>
#include <string.h>

int main()
{
	FILE* pipe;
	char buffer[BUFSIZ+1];
	int num;
	memset(buffer, '\0', sizeof(buffer));
	//pipe=popen("uname -a", "r");
	pipe = popen("ls -lah", "r");
	if(pipe != NULL)
	{
		num=fread(buffer, sizeof(char), BUFSIZ, pipe);
		if(num > 0)
		{
			printf("Read from pipe:\n%s\n", buffer);
		}
		else
		{
			printf("Nothing read from pipe!\n");
		}
		pclose(pipe);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}


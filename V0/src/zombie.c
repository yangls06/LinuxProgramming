/*
 * =====================================================================================
 *
 *       Filename:  zoobie.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/2012 02:13:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid<0){
		printf("error!\n");
		return -1;
	}else if(pid==0){
		exit(0);
		return 0;
	}else{
		sleep(10);
		wait(NULL);
		return 1;
	}
}


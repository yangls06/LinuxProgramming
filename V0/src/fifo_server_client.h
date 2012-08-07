/*
 * =====================================================================================
 *
 *       Filename:  fifo_client_server.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/07/2012 02:24:09 PM
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
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO "/tmp/serv_fifo"
#define CLIENT_FIFO "/tmp/cli_%d_fifo"

#define BUFFER_SIZE 1024

struct data_to_pass_st {
	pid_t client_pid;
	char data[BUFFER_SIZE-1];
};

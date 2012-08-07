/*
 * =====================================================================================
 *
 *       Filename:  fifo_server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/07/2012 02:28:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <ctype.h>
#include "fifo_server_client.h"

int main()
{
	int server_fifo_fd;
	int client_fifo_fd;
	int read_res;
	char client_fifo[256];
	char* tmp_char_ptr;
	struct data_to_pass_st my_data;

	if(access(SERVER_FIFO, F_OK) == -1)
	{
		read_res = mkfifo(SERVER_FIFO, 0777);
		if(read_res != 0)
		{
			fprintf(stderr, "Server %d creating fifo failed\n", getpid());
			exit(EXIT_FAILURE);
		}
	}
	
	server_fifo_fd = open(SERVER_FIFO, O_RDONLY);
	if(server_fifo_fd == -1)
	{
		fprintf(stderr, "Server %d openning fifo failed\n", getpid());
		exit(EXIT_FAILURE);
	}

	sleep(10); /* lets clients queue for demo purposes */
	do {
		read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
		if(read_res > 0) 
		{
			tmp_char_ptr = my_data.data;
			while(*tmp_char_ptr)
			{
				*tmp_char_ptr = toupper(*tmp_char_ptr);
				tmp_char_ptr++;
			}
			
			sprintf(client_fifo, CLIENT_FIFO, my_data.client_pid);
			client_fifo_fd = open(client_fifo, O_WRONLY);
			if(client_fifo_fd != -1)
			{
				write(client_fifo_fd, &my_data, sizeof(my_data));
				close(client_fifo_fd);
			}
		}
	}while(read_res > 0);

	close(server_fifo_fd);
	unlink(SERVER_FIFO);
	exit(EXIT_SUCCESS);
}





















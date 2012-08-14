/*
 * =====================================================================================
 *
 *       Filename:  shm_com.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/14/2012 09:51:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#define TXT_SZ 2048

struct shared_use_st {
	int written;
	char text[TXT_SZ];
};

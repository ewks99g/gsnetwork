
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#ifndef __NETWORK_DEFINE_H__
#define __NETWORK_DEFINE_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>



typedef unsigned int  uint32;
typedef int int32;
typedef unsigned char uint8;
typedef char int8;

///
typedef int THandler;


#define MAX_EPOLL_HINT_FILE_SIZE 1024   //just a hint, make no sense
#define MAX_EPOLL_NETWORK_EVENT_SIZE 8190

#endif		//endof __NETWORK_DEFINE_H__

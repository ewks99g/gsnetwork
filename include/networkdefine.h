
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#ifndef __NETWORK_DEFINE_H__
#define __NETWORK_DEFINE_H__

#include <stdio.h>
#include <stdlib.h>
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
#include <sys/epoll.h>
#include <string.h>
#include "typedef.h"

///
typedef int32 THandler;
#define MAX_EPOLL_HINT_FILE_SIZE 1024   //just a hint, make no sense
#define MAX_EPOLL_NETWORK_EVENT_SIZE 8190
#define MAX_INNER_PORT_LISTEN_BACK_LOG 10
#define MAX_OUTER_PORT_LISTEN_BACK_LOG 100

enum ENetworkMsgType
{
	ENMT_NONE,
	ENMT_TEST_MSG,			//test msg
	ENMT_COUNT
};


#endif		//endof __NETWORK_DEFINE_H__

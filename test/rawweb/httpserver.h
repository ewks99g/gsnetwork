/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/24
******************************************************************/
#ifndef __HTTPSERVER_H_ 
#define __HTTPSERVER_H_ 
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

class HttpServer
{
	public:
		HttpServer();
		~HttpServer();

		bool start(const char* ipstring,unsigned short port);
		void process();
	private:
		struct sockaddr_in      address_;
		int						listenfd_;
};

//////////////////////////////////////////////////////////////
class HttpHandler
{
	public:
		HttpHandler();
		~HttpHandler();
	public:
		void start_handle();
		void set_argument(int fd,struct sockaddr_in& addr);
	private:
		int http_fd_;
		struct sockaddr_in	remote_addr_;
};
/////////////////////////////////////////////////////////////

void* http_thread_routine(void* argument);

#endif

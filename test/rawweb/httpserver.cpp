/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/24
******************************************************************/
#include "httpserver.h"
#include <pthread.h>
HttpServer::HttpServer()
{}

HttpServer::~HttpServer()
{}

bool HttpServer::start(const char* ipstring,unsigned short port)
{
	address_.sin_family = AF_INET;
    address_.sin_port = htons(port);
    if(inet_aton(ipstring,&address_.sin_addr) == 0)
    {   
        return false;
    }   

    listenfd_ = socket(PF_INET,SOCK_STREAM,0);
    if (listenfd_ < 0)
    {   
        return false;
    }   

    if (bind(listenfd_,(struct sockaddr*)&address_, sizeof(struct sockaddr_in)) < 0)
    {   
        return false;
    }   

    if (listen(listenfd_,50) < 0)
    {   
        return false;
    }

	return true;
}

void HttpServer::process()
{
	while (1) {
		struct sockaddr_in req_addr;
		memset(&req_addr,0,sizeof(struct sockaddr_in));

		socklen_t  addr_len = 0;
		int requestfd = accept(listenfd_,(struct sockaddr *)&req_addr,&addr_len);
		if (requestfd > 0) {
			HttpHandler* http_handler = new HttpHandler();
			pthread_t thread_id;
			if (pthread_create(&thread_id, NULL, &http_thread_routine, http_handler) < 0)
				perror("Create thread of http handler");
		}

		printf("circle onec\n");
	}
}
//////////////////////////////////////////////////////////////////////

HttpHandler::HttpHandler() : http_fd_(0)
{
	memset(&remote_addr_,0,sizeof(struct sockaddr_in));
}

HttpHandler::~HttpHandler()
{
}

void HttpHandler::set_argument(int fd,struct sockaddr_in& addr)
{
	http_fd_ = fd;
	memcpy(&remote_addr_,&addr,sizeof(struct sockaddr_in));
}

void HttpHandler::start_handle()
{
	printf("start handler http");
	delete this;
}

//////////////////////////////////////////////////////////////////////

void* http_thread_routine(void* argument)
{
	if (argument) {
		HttpHandler* http_handler = (HttpHandler*)argument;
		http_handler->start_handle();
	}
}

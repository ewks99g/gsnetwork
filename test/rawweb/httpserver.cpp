/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/24
******************************************************************/
#include <pthread.h>
#include <assert.h>
#include "httpserver.h"
HttpServer::HttpServer()
{}

HttpServer::~HttpServer()
{}

bool HttpServer::start(const char* ipstring,unsigned short port)
{
	address_.sin_family = AF_INET;
    address_.sin_port = htons(port);
    if (inet_aton(ipstring,&address_.sin_addr) == 0)
        return false;

    listenfd_ = socket(PF_INET,SOCK_STREAM,0);
    if (listenfd_ < 0)
        return false;

	int option = 1;
	if (setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
		return false;

    if (bind(listenfd_,(struct sockaddr*)&address_, sizeof(struct sockaddr_in)) < 0)
        return false;

    if (listen(listenfd_,50) < 0)
        return false;

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
			http_handler->set_argument(requestfd,req_addr);

			pthread_t thread_id;
			if (pthread_create(&thread_id, NULL, &http_thread_routine, http_handler) < 0)
				perror("Create thread of http handler");
			else
				printf("rcv conn\n");
		}
	}
}
//////////////////////////////////////////////////////////////////////

HttpHandler::HttpHandler() : http_fd_(0)
{
	memset(&remote_addr_,0,sizeof(struct sockaddr_in));
	memset(&http_line_[0],0,MAX_HTTP_LINE_SIZE);
	memset(&http_arg_info_[0],0,sizeof(http_arg_info_));
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
	
	sock_file_ = fdopen(http_fd_,"a+");
	if (NULL == sock_file_)
		_clear_data();

	while (fgets(http_line_,MAX_HTTP_LINE_SIZE,sock_file_)) {
		printf("%s\n",http_line_);
		memset(&http_line_[0],0,MAX_HTTP_LINE_SIZE);
	}
	
	_clear_data();
	printf("exit thread\n");
}

void HttpHandler::_clear_data()
{
	if (sock_file_)
		fclose(sock_file_);
	else
		close(http_fd_);
	
	delete this;
}

int HttpHandler::set_http_field(const char* key,const char* value)
{
	for (int i = 0; i < MAX_HTTP_FIELD_PAIR_NUM; i++) {
		if (http_arg_info_[i].key == 0) {
			http_arg_info_[i].key = key;
			assert(strlen(value) < MAX_HTTP_FIELD_VALUE_LEN);
			strcpy(http_arg_info_[i].value,value);

			return 0;
		}
	}
	return -1;
}

char* HttpHandler::get_http_field(const char* key)
{
	for (int i = 0; i < MAX_HTTP_FIELD_PAIR_NUM; i++) {
		if (http_arg_info_[i].key != 0 && strcmp(http_arg_info_[i].key,key) == 0) {
			return &http_arg_info_[i].value[0];
		}
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////

void* http_thread_routine(void* argument)
{
	if (argument) {
		HttpHandler* http_handler = (HttpHandler*)argument;
		http_handler->start_handle();
	}
}
//////////////////////////////////////////////////////////////////////


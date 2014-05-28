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
//////////////////////////////////////////////////////////////////////
#define MAX_HTTP_LINE_SIZE 2049
#define MAX_HTTP_METHOD_LEN 10

#define MAX_HTTP_FIELD_VALUE_LEN 255
struct HttpKeyValue
{
	const char *key;
	char	    value[MAX_HTTP_FIELD_VALUE_LEN];
};
#define MAX_HTTP_FIELD_PAIR_NUM 10

/*
 * The routine of http server spawned thread 
 * */
void* http_thread_routine(void* argument);

/*
 *The function of user interface
 * */
/////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////
class HttpDataEntry
{
	public:
		HttpDataEntry() {}
		~HttpDataEntry() {}
	public:
		const char* getValue(const char* key) const;
};

//////////////////////////////////////////////////////////////
class HttpHandler
{
	public:
		HttpHandler();
		~HttpHandler();
	public:
		void start_handle();
		void set_conn_info(int fd,struct sockaddr_in& addr);

		int set_http_field(const char* key,const char* value);
		char* get_http_field(const char* key);
	private:
		int _read_request();
		int _split_uri(const char* httpuri,const char spliter);
		void _clear_data();
	private:
		int					http_fd_;
		struct sockaddr_in	remote_addr_;
		FILE*				sock_file_;
		char				http_option_data_[MAX_HTTP_LINE_SIZE];
		char				http_request_[MAX_HTTP_LINE_SIZE];

		HttpKeyValue		http_arg_info_[MAX_HTTP_FIELD_PAIR_NUM];

		HttpDataEntry		http_data_accessor_;

		int					handle_in_pipe_[2];
		int					handle_out_pipe_[2];
};
////////////////////////////////////////////////////////////

#endif

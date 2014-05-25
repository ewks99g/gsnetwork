/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/24
******************************************************************/
#include "httpserver.h"

int
main(int argc,char** argv)
{
	HttpServer _server;
	if (_server.start("192.168.1.113",8001))
		_server.process();
}

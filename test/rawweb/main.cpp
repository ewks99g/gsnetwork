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
	if (argc < 3)
	{
		return 1;
	}
	
	HttpServer _server;
	if (_server.start(argv[1],atoi(argv[2])))
		_server.process();
}

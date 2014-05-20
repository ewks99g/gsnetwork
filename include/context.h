/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#ifndef __INCLUDE_CONTEXT_H_
#define __INCLUDE_CONTEXT_H_

#include "epoll.h"
#include "thread.h"
#include "ipcbase.h"

class MultiplexContext
{
	public:
		MultiplexContext();
		virtual ~MultiplexContext();
	public:
		bool add_net_node(IoEvent* object,int32 eventflag);
		bool rmv_net_node(IoEvent* object);
		bool start_run();
	private:
		Epoll		poll_;
};

#endif

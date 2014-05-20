/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#include "context.h"

MultiplexContext::MultiplexContext()
{

}

MultiplexContext::~MultiplexContext()
{

}

bool MultiplexContext::start_run()
{
	poll_.start();
}

bool MultiplexContext::add_net_node(IoEvent* object,int32 eventflag)
{	
	if (!poll_.add_handler(object->handle(),object,eventflag))
	{
		return false;
	}
	return true;
}

bool MultiplexContext::rmv_net_node(IoEvent* object)
{	
	if (!poll_.rmv_handler(object->handle()))
	{
		return false;
	}
	return true;
}

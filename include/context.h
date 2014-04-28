/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#pragma once
#include "epoll.h"
#include "thread.h"

class CMultiplexContext
{
	public:
		CMultiplexContext();
		~CMultiplexContext();
	public:
		bool addAcceptor(const char* ipstring,uint16 port);
		bool addConnctor(const char* ipstring,uint16 port);
		bool addFifo(const char* ipcstring);
		bool startRun();
	private:
		CEpoll		m_poll;
};


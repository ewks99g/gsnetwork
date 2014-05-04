/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#include "context.h"

CMultiplexContext::CMultiplexContext()
{

}

CMultiplexContext::~CMultiplexContext()
{

}

bool CMultiplexContext::startRun()
{
	m_poll.start();
}

bool CMultiplexContext::addNetNode(CIoEvent* object,int32 eventflag)
{	
	if (!m_poll.addHandler(object->handle(),object,eventflag))
	{
		return false;
	}
	return true;
}

bool CMultiplexContext::rmvNetNode(CIoEvent* object)
{	
	if (!m_poll.rmvHandler(object->handle()))
	{
		return false;
	}
	return true;
}


//bool CMultiplexContext::addAcceptor(const char* ipstring,uint16 port)
//{
//	
//}
//
//bool CMultiplexContext::addConnctor(const char* ipstring,uint16 port)
//{
//
//}
//
//bool CMultiplexContext::addFifo(const char* ipcstring)
//{
//
//}


/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once

#include "networkdefine.h"

class CIoEvent
{
	public:
		CIoEvent() {}
		~CIoEvent() {}

	protected:
	/*
	 * This method is used to handle the input event from event listener,i.e. epoll.
	 * */
	virtual void inEvent() = 0;
	
	/*
	 *This method is used to handler the output event from event listener,i.e. epoll.
	 * */
	virtual	void outEvent() = 0;

	/*
	 *This method is used to handler the timeout event from event listener,i.e. epoll.
	 * */
	virtual	void timeEvent() = 0;
};

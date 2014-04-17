
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
	public:
	
	/*
	 * This method is used to handle the input event from event listener,i.e. epoll.
	 * */
	virtual void in_event() = 0;
	
	/*
	 *This method is used to handler the output event from event listener,i.e. epoll.
	 * */
	virtual	void out_event() = 0;

	/*
	 *This method is used to handler the timeout event from event listener,i.e. epoll.
	 * */
	virtual	void time_event() = 0;
};

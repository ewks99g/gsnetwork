
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once

#include "networkdefine.h"

class MultiplexContext;
class IoEvent
{
	public:
		IoEvent(MultiplexContext* pcontext) {context_ = pcontext;}
		~IoEvent() {}

	public:
		/*
  		 * This method is used to handle the input event from event listener,i.e. epoll.
  		 * */
  		virtual void in_event() = 0;

		/*
  		 * This method is used to handle the error event from event listener,i.e. epoll.
  		 * */
  		virtual void error_event() = 0;
  		
  		/*
  		 *This method is used to handler the output event from event listener,i.e. epoll.
  		 * */
  		virtual	void out_event() = 0;
  	
  		/*
  		 *This method is used to handler the timeout event from event listener,i.e. epoll.
  		 * */
  		virtual	void time_event() = 0;
  	
  		/*
  		 * This method is used to get the handler associated with event
  		 * */
  		THandler handle() {return event_handler_;}
	protected:
		THandler				event_handler_;
		struct sockaddr_in      address_; 

		MultiplexContext*		context_;
};

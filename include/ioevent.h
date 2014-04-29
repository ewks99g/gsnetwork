
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once

#include "networkdefine.h"

class CMultiplexContext;
class CIoEvent
{
	public:
		CIoEvent(CMultiplexContext* pcontext) {m_pContext = pcontext;}
		~CIoEvent() {}

	public:
		/*
  		 * This method is used to handle the input event from event listener,i.e. epoll.
  		 * */
  		virtual void inEvent() = 0;

		/*
  		 * This method is used to handle the error event from event listener,i.e. epoll.
  		 * */
  		virtual void errorEvent() = 0;
  		
  		/*
  		 *This method is used to handler the output event from event listener,i.e. epoll.
  		 * */
  		virtual	void outEvent() = 0;
  	
  		/*
  		 *This method is used to handler the timeout event from event listener,i.e. epoll.
  		 * */
  		virtual	void timeEvent() = 0;
  	
  		/*
  		 * This method is used to get the handler associated with event
  		 * */
  		THandler handle() {return m_nHandler;}
	protected:
		THandler				m_nHandler;
		struct sockaddr_in      m_uAddress; 

		CMultiplexContext*		m_pContext;
};

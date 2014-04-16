/******************************************************************* 
 **  Copyright(c) 2000-2013 linghegu
 **  All rights reserved. 
 **  Author:     wangbin
 **  Email:      wang70bin@163.com
 **  CreateTime: 2014/4/15  
 *******************************************************************/
#include "epoll.h"

CEpoll::CEpoll()
{
   m_nEpollHandler = epoll_create(MAX_EPOLL_HINT_FILE_SIZE);
   if (m_nEpollHandler < 0)
   {
      output_error("Start Epoll Instance");
   }
}

CEpoll::~CEpoll()
{

}

bool CEpoll::addHandler(THandler handler,CIoEvent* ioevent)
{
	epoll_event _event;
	_event.events = 0;
	_event.data.ptr = ioevent;

	int32 _result = epoll_ctl(m_nEpollHandler, EPOLL_CTL_ADD, handler, &_event);
	if (_result < 0)
	{
		output_error("Epoll Add Handler");
		return false;
	}

	return true;
}

bool CEpoll::rmvHandler(THandler handler)
{
	epoll_event _event;
	memset(&_event,0,sizeof(epoll_event));

	int32 _result = epoll_ctl(m_nEpollHandler, EPOLL_CTL_DEL, handler, &_event);
    if (_result < 0)
    {
        output_error("Epoll Add Handler");
 	    return false;
    }
		    
   return true;
}

bool CEpoll::start()
{
	m_work.start(CEpoll::workerRoutine,this);
}

void CEpoll::loop()
{
	while (true)
	{
		int32 _eventCnt = epoll_wait(m_nEpollHandler,m_vEventCache,MAX_EPOLL_NETWORK_EVENT_SIZE,-1);
		for(_i =0;_i < _eventCnt; ++_i)
		{
			 CIoEvent* _ioEvent = ((poll_entry_t*) ev_buf [i].data.ptr);     
			 if (pe->fd == retired_fd)
			 continue; 
			 if (ev_buf [i].events & (EPOLLERR | EPOLLHUP))     
			 	pe->events->in_event (); 
			 if (pe->fd == retired_fd) 
			 	continue;   
			if (ev_buf [i].events & EPOLLOUT) 
				pe->events->out_event ();  
			if (pe->fd == retired_fd)            
				continue;   
			if (ev_buf [i].events & EPOLLIN)    
				pe->events->in_event ();
		}
	}
}

void CEpoll::workerRoutine (void* arg)
{
	(CEpoll*)arg()->loop();
}
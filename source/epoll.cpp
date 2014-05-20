/******************************************************************* 
 **  Copyright(c) 2000-2013 linghegu
 **  All rights reserved. 
 **  Author:     wangbin
 **  Email:      wang70bin@163.com
 **  CreateTime: 2014/4/15  
 *******************************************************************/
#include "epoll.h"

Epoll::Epoll()
{
   epoll_handler_ = epoll_create(MAX_EPOLL_HINT_FILE_SIZE);
   if (epoll_handler_ < 0)
   {
      output_error("Start Epoll Instance");
   }
}

Epoll::~Epoll()
{

}

bool Epoll::add_handler(THandler handler,IoEvent* ioevent,int32 eventflag)
{
	epoll_event _event;
	_event.events = eventflag;
	_event.data.ptr = ioevent;

	int32 _result = epoll_ctl(epoll_handler_, EPOLL_CTL_ADD, handler, &_event);
	if (_result < 0)
	{
		output_error("Epoll Add Handler");
		return false;
	}
	return true;
}

bool Epoll::rmv_handler(THandler handler)
{
	epoll_event _event;
	memset(&_event,0,sizeof(epoll_event));

	int32 _result = epoll_ctl(epoll_handler_, EPOLL_CTL_DEL, handler, &_event);
    if (_result < 0)
    {
        output_error("Epoll Add Handler");
 	    return false;
    }
		    
   return true;
}

bool Epoll::start()
{
	worker_.start(Epoll::worker_routine,this);
}

void Epoll::loop()
{
	while (true)
	{
		int32 _eventCnt = epoll_wait(epoll_handler_,event_cache_,MAX_EPOLL_NETWORK_EVENT_SIZE,-1);
		for(int32 _i =0;_i < _eventCnt; ++_i)
		{
			IoEvent* _ioEvent = ((IoEvent*)event_cache_[_i].data.ptr);
			if (!_ioEvent)
				continue;
			
			printf("rcvb evnt\n");
			if (event_cache_[_i].events & (EPOLLERR | EPOLLHUP))     
			{
				 _ioEvent->error_event(); 
			}

			if (event_cache_[_i].events & EPOLLIN)
			{
				_ioEvent->in_event();
			}
		}
	}
}

void Epoll::worker_routine(void* arg)
{
	if (arg)
	{
		((Epoll*)arg)->loop();
	}
}

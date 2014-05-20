/*
 * Implement one epoll component
 *
 * */
#ifndef __INCLUDE_EPOLL_H_
#define __INCLUDE_EPOLL_H_

#include "networkdefine.h"
#include "err.h"
#include "ioevent.h"
#include "thread.h"

class Epoll 
{
	public:
		Epoll();
		~Epoll();
	public:
		bool start();
		void loop();
		bool add_handler(THandler handler,IoEvent* ioevent,int32 eventflag);
		bool rmv_handler(THandler handler);

		 //  Main worker thread routine.        
		 static void worker_routine (void* arg);
	private:
		THandler 		epoll_handler_;
		epoll_event		event_cache_[MAX_EPOLL_NETWORK_EVENT_SIZE];

		Thread			worker_;
};
#endif

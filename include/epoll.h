#pragma once
#include "networkdefine.h"
#include "err.h"
#include "ioevent.h"
#include "thread.h"

class CEpoll 
{
	public:
		CEpoll();
		~CEpoll();
	public:
		bool start();
		void loop();
		bool addHandler(THandler handler,CIoEvent* ioevent,int32 eventflag);
		bool rmvHandler(THandler handler);

		 //  Main worker thread routine.        
		 static void workerRoutine (void* arg);
	private:
		THandler 		m_nEpollHandler;
		epoll_event		m_vEventCache[MAX_EPOLL_NETWORK_EVENT_SIZE];

		CThread			m_worker;
};

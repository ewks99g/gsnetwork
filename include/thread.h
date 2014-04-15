
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 ******************************************************************/
#pragma once

#include <pthread.h>


typedef void (thread_fn) (void*);

class CThread
{
	public:
		
		int32		start(thread_fn tfn,void* arg);
		int32		stop();
	private:
		pthread_t	m_nThreadId;
		thread_fn	m_fThreadRoutine;
		void*		m_pArg;
};






























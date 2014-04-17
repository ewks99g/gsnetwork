
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *  Author: 	wangbin
 *  Email:  	wang70bin@163.com
 *  CreateTime: 2014/4/15  
 ******************************************************************/
#pragma once

#include <pthread.h>
#include "networkdefine.h"

typedef void (thread_fn) (void*);

class CThread
{
	public:
		CThread();
		~CThread();
	public:
		int32		start(thread_fn* tfn,void* arg);
		int32		stop();

		/*
		 * This static method can be used to separate user's passed routine
		 * */
	   static void *threadRoutine (void *arg);
	private:
		pthread_t	m_nThreadId;

	public:
		thread_fn*	m_fThreadRoutine;
		void*		m_pArg;
};

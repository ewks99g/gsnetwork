
/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *   
 *  文件名称: define a thread
 *  简要描述: 
 *   
 *  创建日期: 2014/4/14
 *  作者:	      wangbin
 *  说明: 	      
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






























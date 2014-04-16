/******************************************************************* 
 **  Copyright(c) 2000-2013 linghegu
 **  All rights reserved. 
 **  Author:     wangbin
 **  Email:      wang70bin@163.com
 **  CreateTime: 2014/4/15  
 *******************************************************************/

#include "thread.h"

CThread::CThread()
{
}

CThread::~CThread()
{
}

void* CThread::threadRoutine (void *arg)
{
	CThread* _self = (CThread*)arg;
	_self->m_fThreadRoutine(_self->m_pArg);
}

int32 CThread::start(thread_fn tfn,void* arg)
{
	m_fThreadRoutine = tfn;
	m_pArg = arg;

	 int32 _result = pthread_create (&m_nThreadId, NULL, CThread::thread_routine, this);
	 if (_result < 0)
	 {
	 	output_error("Create Thread");
		return -1;
	 }

	 return 0;
}

int32 CThread::stop()
{
	return 0;
}

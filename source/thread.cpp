/******************************************************************* 
 **  Copyright(c) 2000-2013 linghegu
 **  All rights reserved. 
 **  Author:     wangbin
 **  Email:      wang70bin@163.com
 **  CreateTime: 2014/4/15  
 *******************************************************************/

#include "thread.h"
#include "err.h"

Thread::Thread()
{
}

Thread::~Thread()
{
}

void* Thread::thread_routine (void *arg)
{
	Thread* _self = (Thread*)arg;
	_self->thread_routine_(_self->ptr_arg_);
}

int32 Thread::start(thread_fn* tfn,void* arg)
{
	thread_routine_ = tfn;
	ptr_arg_ = arg;

	 int32 _result = pthread_create(&threadid_, NULL, Thread::thread_routine, this);
	 if (_result < 0)
	 {
	 	output_error("Create Thread");
		return -1;
	 }

	 return 0;
}

int32 Thread::stop()
{
	return 0;
}

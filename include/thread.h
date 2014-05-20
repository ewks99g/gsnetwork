
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

class Thread
{
	public:
		Thread();
		~Thread();
	public:
		int32		start(thread_fn* tfn,void* arg);
		int32		stop();

		/*
		 * This static method can be used to separate user's passed routine
		 * */
	   static void *thread_routine (void *arg);
	private:
		pthread_t	threadid_;

	public:
		thread_fn*	thread_routine_;
		void*		ptr_arg_;
};

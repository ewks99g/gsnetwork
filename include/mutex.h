/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/06
******************************************************************/
#pragma once
#include <pthread.h>
#include <stdio.h>

/*
*
* Simple Mutex implement
*/
class Mutex
{   
public:
    Mutex()
    {   
        if (pthread_mutex_init (&mutex_, NULL) < 0)
			printf("create lock errror\n");
    }   

    ~Mutex()
    {   
        if (pthread_mutex_destroy (&mutex_) < 0)
			printf("destroy lock errror\n");
    }   

    inline void lock()
    {   
        if (pthread_mutex_lock (&mutex_) < 0)
			printf("lock errror\n");
    }   

    inline void unlock()
    {   
        if (pthread_mutex_unlock (&mutex_) < 0)
			printf("unlock errror\n");
    }   

private:

    pthread_mutex_t mutex_;
};

/*
*
* Implement a scope mutex
*/
class ScopeGuard
{
	public:
		inline ScopeGuard(Mutex& mutex) : mutex_(mutex)
		{
			mutex_.lock();
		}
		inline ~ScopeGuard()
		{
			mutex_.unlock();
		}
	private:
		Mutex&	mutex_;
};

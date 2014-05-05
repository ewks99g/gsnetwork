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
class CMutex
{   
public:
    inline CMutex ()
    {   
        int _result = pthread_mutex_init (&m_mutex, NULL);
		if (_result < 0)
		{
			printf("create lock errror\n");
		}
    }   

    inline ~CMutex ()
    {   
        int _result = pthread_mutex_destroy (&m_mutex);
		if (_result < 0)
		{
			printf("destroy lock errror\n");
		}

    }   

    inline void lock ()
    {   
        int _result = pthread_mutex_lock (&m_mutex);
		if (_result < 0)
		{
			printf("lock errror\n");
		}

    }   

    inline void unlock ()
    {   
        int _result = pthread_mutex_unlock (&m_mutex);
		if (_result < 0)
		{
			printf("unlock errror\n");
		}

    }   

private:

    pthread_mutex_t m_mutex;
};


/*
*
* Implement a scope mutex
*/
class CGuard
{
	public:
		inline CGuard(CMutex& mutex) : m_mutex(mutex)
		{
			m_mutex.lock();
		}
		inline ~CGuard()
		{
			m_mutex.unlock();
		}
	private:
		CMutex&	m_mutex;
};

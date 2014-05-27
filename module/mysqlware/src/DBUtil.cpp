/********************************************************************
	created:	2010/07/09
	created:	9:7:2010   16:32
	filename: 	CharacterTransform.cpp
	file path:	Mysqlware\Mysqlware
	file base:	CharacterTransform
	file ext:	cpp
	author:		jhf
	
	purpose:	
*********************************************************************/
#include "DBUtil.h"

#ifdef __FreeBSD__
#  define DB_PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE
#else
#  define DB_PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#endif

#define DB_UNICODE_CHARS (sizeof(wchar_t) >= 4 ? 0x110000 : 0x10000)


db_int32 dTransForm::t_utf8_to_unicode (char *s, db_int32 len)
{
	db_int32 length = 0;
	char *t = s;

	length = 0;
	while (s - t < len)
	{
		if (*(unsigned char *) s <= 0x7f)	/* one byte */
		{
			*s++;		/* expand with 0s */
		}
		else if (*(unsigned char *) s <= 0xdf)	/* 2 byte */
		{
			s += 2;
		}
		else			/* 3 byte */
		{
			s += 3;
		}
		length++;
	}
	return (length);
}

db_int32 dTransForm::t_unicode_to_utf8 (wchar_t *us,  db_int32 wLen)
{
	db_int32 length = 0;
	db_int32 __i = 0;

	for (__i = 0; __i < wLen ; __i++)
	{
		wchar_t mychar = us[__i];
		if (mychar <= 0x7F)
		{			/* 7 sig bits */			
			length++;
		}
		else if (mychar <= 0x7FF)
		{			/* 11 sig bits */
			length += 2;
		}
		else if (mychar <= 0xFFFF)
		{			/* 16 sig bits */
			length += 3;
		}
		else if (mychar < DB_UNICODE_CHARS)
		{			/* 21 sig bits */
			length += 4;
		}
	}

	return (length);
}

db_int32 dTransForm::utf8_to_unicode (char *s, db_int32 len, wchar_t *us)
{
	db_int32 length = 0;
	char *t = s;

	length = 0;
	while (s - t < len)
	{
		if (*(unsigned char *) s <= 0x7f)	/* one byte */
		{
			*us++ = *s++;		/* expand with 0s */
		}
		else if (*(unsigned char *) s <= 0xdf)	/* 2 byte */
		{
			*us++ =
				((*(unsigned char *) s & 0x1f) << 6) +
				((*(unsigned char *) (s + 1)) & 0x3f);
			s += 2;
		}
		else			/* 3 byte */
		{
			*us++ =
				((db_int32) (*(unsigned char *) s & 0x0f) << 12) +
				((*(unsigned char *) (s + 1) & 0x3f) << 6) +
				(*(unsigned char *) (s + 2) & 0x3f);
			s += 3;
		}
		length++;
	}
	*us = 0;
	return (length);
}

db_int32 dTransForm::unicode_to_utf8 (wchar_t *us,  db_int32 wLen, char *s)
{
	db_int32 __i = 0;
	char *t = s;

	for (__i = 0; __i < wLen ; __i++)
	{
		wchar_t mychar = us[__i];
		if (mychar <= 0x7F)
		{			/* 7 sig bits */
			*t++ = (char)mychar;
		}
		else if (mychar <= 0x7FF)
		{			/* 11 sig bits */
			*t++ = 0xC0 | (unsigned char) (mychar >> 6);	/* upper 5 bits */
			*t++ = 0x80 | (unsigned char) (mychar & 0x3F);	/* lower 6 bits */
		}
		else if (mychar <= 0xFFFF)
		{			/* 16 sig bits */
			*t++ = 0xE0 | (unsigned char) (mychar >> 12);	/* upper 4 bits */
			*t++ = 0x80 | (unsigned char) ((mychar >> 6) & 0x3F);	/* next 6 bits */
			*t++ = 0x80 | (unsigned char) (mychar & 0x3F);	/* lowest 6 bits */
		}
#ifdef LINUX
		else if (mychar < DB_UNICODE_CHARS)
		{			/* 21 sig bits */
			*t++ = 0xF0 | (unsigned char) ((mychar >> 18) & 0x07);	/* upper 3 bits */
			*t++ = 0x80 | (unsigned char) ((mychar >> 12) & 0x3F);	/* next 6 bits */
			*t++ = 0x80 | (unsigned char) ((mychar >> 6) & 0x3F);	/* next 6 bits */
			*t++ = 0x80 | (unsigned char) (mychar & 0x3F);	/* lowest 6 bits */
		}
#endif
	}
	*t = 0;

	return (db_int32)(t - s);
	return 0;
}

db_int32 dTransForm::wcslen(wchar_t* us)
{
	db_int32 length = 0;
	wchar_t* t = us;
	while (*t != '\0')
	{
		length++;
		++t;
	}
	return length;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
#ifndef MYSQLWARE_WIN32

dThread::dThread ()
{
	m_nThreadID = 0;
}

dThread::~dThread ()
{

}

static void *thread_start_routine(void *pVoid)
{
	dThread *_pThis = (dThread *)pVoid;
	_pThis->run();

	return 0;
}

void dThread::start (void)
{
	int rc = pthread_create  (&m_nThreadID, 0, thread_start_routine, (void *)this);	
	if (rc)
	{
		PRINTFERROR();
	}
}

void dThread::terminate(void)
{
	pthread_cancel (m_nThreadID);
}

void dThread::wait(void)
{
	pthread_join (m_nThreadID, NULL);
}


pthread_mutexattr_t dMutex::m_attr;
db_int32 dMutex::m_attr_refcount = 0;

dMutex::dMutex ()
{
	if (!m_attr_refcount++)
	{
		pthread_mutexattr_init (&m_attr);
		pthread_mutexattr_settype (&m_attr, DB_PTHREAD_MUTEX_RECURSIVE);
	}

	pthread_mutex_init (&m_mutex, &m_attr);
}

dMutex::~dMutex ()
{
	pthread_mutex_destroy (&m_mutex);
	if (!--m_attr_refcount)
		pthread_mutexattr_destroy (&m_attr);
}

bool dMutex::lock ()
{
	return (pthread_mutex_lock (&m_mutex) == 0);
}

bool dMutex::tryLock ()
{
	return (pthread_mutex_trylock (&m_mutex) == 0);
}

void dMutex::unlock ()
{
	pthread_mutex_unlock (&m_mutex);
}


#else                                                       //windows

dThread::dThread()
{
	m_hThreadHandle = NULL;
}

dThread::~dThread ()
{
	if (m_hThreadHandle)
	{
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}
}

unsigned long __stdcall thread_start_routine(void *pVoid)
{
	dThread *_pThis = (dThread *)pVoid;
	_pThis->run();

	return 0;
}

void dThread::start (void)
{
	db_DWORD _dwThreadID = 0;
	m_hThreadHandle = CreateThread (0, 0, thread_start_routine, (void *)this, 0, &_dwThreadID);	
	if (m_hThreadHandle == NULL)
	{
		PRINTFERROR();
	}

}

void dThread::terminate(void)
{
	if (m_hThreadHandle)
	{
		TerminateThread(m_hThreadHandle, 0);
		m_hThreadHandle = 0;
	}
}

void dThread::wait(void)
{
	WaitForSingleObject(m_hThreadHandle, INFINITE);
}

dMutex::dMutex ()
{
	m_hMutex = CreateMutex (NULL, FALSE, NULL);
	if (m_hMutex == NULL)
	{
		PRINTFERROR();
	}
}

dMutex::~dMutex ()
{
	CloseHandle (m_hMutex);
}

bool dMutex::lock ()
{
	return (WaitForSingleObject (m_hMutex, INFINITE) != WAIT_FAILED);
}

bool dMutex::tryLock ()
{
	DWORD _nState = WaitForSingleObject (m_hMutex, 0);
	return (_nState == WAIT_OBJECT_0) && (_nState != WAIT_ABANDONED);
}

void dMutex::unlock ()
{
	ReleaseMutex (m_hMutex);
}

#endif


dMutexGuard::dMutexGuard(dMutex &mutex) : m_mutex(mutex)
{
	m_mutex.lock();
}

dMutexGuard::~dMutexGuard(void)
{
	m_mutex.unlock();
}





























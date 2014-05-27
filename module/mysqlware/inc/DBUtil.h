/********************************************************************
	created:	2010/07/09
	created:	9:7:2010   16:31
	filename: 	CharacterTransform.h
	file path:	Mysqlware\Mysqlware
	file base:	CharacterTransform
	file ext:	h
	author:		jhf
	
	purpose:	
*********************************************************************/
#ifndef _CHARACTER_TRANSFORM_H
#define _CHARACTER_TRANSFORM_H

#include "DBDefine.h"

#ifndef MYSQLWARE_WIN32
#include <pthread.h>
#else
#include <windows.h>
#include <process.h>
#endif


class dTransForm
{
public:
	dTransForm() {}
	~dTransForm() {}
public:
	/// 测试长度
	static db_int32 t_utf8_to_unicode (char *s, db_int32 len);
	static db_int32 t_unicode_to_utf8 (wchar_t *us, db_int32 wLen);
	/// 字符转换
	static db_int32 utf8_to_unicode (char *s, db_int32 len, wchar_t *us);
	static db_int32 unicode_to_utf8 (wchar_t *us, db_int32 wLen, char *s);
	
	static db_int32 wcslen(wchar_t* us);
};


class dThread
{
public:
	dThread ();
	virtual ~dThread ();

	void start (void);
	/// 终止线程
	void terminate(void);
	/// 等待线程结束
	void wait(void);

#ifdef MYSQLWARE_WIN32
	HANDLE m_hThreadHandle;
#else
	pthread_t m_nThreadID;
#endif
public:
	virtual db_uint32 run() = 0;
};

class dMutex 
{
public:
	dMutex ();
	virtual ~dMutex ();
public:
	bool lock ();
	bool tryLock ();
	void unlock ();
private:
#ifdef MYSQLWARE_WIN32
	HANDLE m_hMutex;
#else
	pthread_mutex_t	m_mutex;
	static pthread_mutexattr_t m_attr;
	static db_int32 m_attr_refcount;
#endif
};

class dNullMutex
{
public:
	dNullMutex() {}
	virtual ~dNullMutex() {}
public:
	bool lock() { return true; }
	bool tryLock() { return true; }
	void unLock() {}
};

class dMutexGuard
{
public:
	explicit dMutexGuard(dMutex &mutex);
	~dMutexGuard(void);
private:
	dMutex	&m_mutex;
};



/*
template <class T, class mutex >
class dQueue
{
public:
	dQueue();
	~dQueue();
public:
	bool isEmpty();
	T* pop();
	void push(T *&ptr);
	db_int32 getCount() { return m_nCount; }
private:
	T *m_pHead;
	T *m_pTail;
	db_int32 m_nCount;
	mutex m_Mutex;
};

template <class T, class mutex >
dQueue<T, mutex>::dQueue() : m_pHead(NULL), m_pTail(NULL), m_nCount(0)
{
}

template <class T, class mutex >
dQueue<T, mutex>::~dQueue()
{
}

template <class T, class mutex >
bool dQueue<T, mutex>::isEmpty()
{
	return m_pHead == 0 ? true : false;
}

template <class T, class mutex >
T* dQueue<T, mutex>::pop()
{
	dMutexGuard lock(m_Mutex);
	T* _elem = m_pHead;
	if (_elem)
	{
		m_pHead = m_pHead->_next;
		if (m_pHead == 0)
		{
			m_pTail = 0;
		}
	}

	m_nCount--;
	return _elem;
}

template <class T, class mutex >
void dQueue<T, mutex>::push(T *&ptr)
{
	dMutexGuard lock(m_Mutex);
	if (m_pTail)
	{
		m_pTail->_next = ptr;
		m_pTail = m_pTail->_next;
	}
	else
	{
		m_pTail = ptr;
		m_pHead = m_pTail;
	}

	m_nCount++;
}

*/

#endif ///_CHARACTER_TRANSFORM_H



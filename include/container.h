/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/05
******************************************************************/
#pragma once


template<class T, int size>
class CCircleQueue
{
	public:	CCircleQueue()	
	{	
		m_size = size;	
		m_head = 0;	
		m_tail = 0;	
		m_nPopPos = 0;
		m_nPushPos = 0;
		m_array = new T[size];		
		for (int __i = 0; __i < m_size; __i++)	
		{	
			m_array[__i] = NULL;
		}
	};
	~CCircleQueue()
	{
	};		
	T pop()
	{
		m_nPopPos = (m_head + 1) % m_size;
		m_temp = m_array[m_nPopPos];
		if (!m_temp)	
		{	
			return NULL;
		}			
		m_array[m_nPopPos] = NULL;	
		m_head = m_nPopPos;		
		return m_temp;
	};	
	bool push(T obj)
	{	
		m_nPushPos = (m_tail + 1) % m_size;	
		if (m_array[m_nPushPos] != NULL)	
		{	
			return false;
		}
		m_array[m_nPushPos] = obj;
		m_tail = m_nPushPos;	
		return true;
		};	
		bool isFull()	
		{
			return ((m_tail + 1) % m_size) == m_head;
		}	
		bool isEmpty()
		{	
			return m_tail == m_head;	
		}
		
		private:	T*	m_array;		
		int m_size;	
		int m_head;		
		int m_tail;		
		T   m_temp;
		int m_nPopPos;	
		int m_nPushPos;
	};

template <typename T,int size>
class blockQueue
{
public:
    blockQueue()
    {
        m_initSize = size;
        
        initQueue();
    }
    virtual ~blockQueue(){}
    
private:
    bool push(T* obj)
    {
        if (!m_objQueue.isFull())
        {
            m_objQueue.push(obj);
            return true;;
        }
        else
        {
            return false;
        }
    }
    
    T* pop()
    {
        if (!m_objQueue.isEmpty())
        {
            return m_objQueue.pop();
        }
        return NULL;
    }
    
public:
    T* allocate()
    {
        return pop();
    }
    bool free(T* obj)
    {
        if (obj == NULL)
            return false;
        
        return push(obj);
    }

protected:
    void initQueue()
    {
        char* _blockBuff = new char[m_initSize * sizeof(T)];
        
        for (int _i = 0; _i < m_initSize; _i++)
        {
            T* _tmpValue = new (&_blockBuff[_i*sizeof(T)])T;
            
            push(_tmpValue);
        }
        
    }
    
private:
//    std::queue<T*> ;
    CCircleQueue<T*,size> m_objQueue;
    int m_initSize;
  
};

#endif

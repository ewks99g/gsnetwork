/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *  Author: 	wangbin
 *  Email:  	wang70bin@163.com
 *  CreateTime: 2014/4/15  
 ******************************************************************/
#pragma once

//#include "frameworkdefine.h"
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "mutex.h"

template<class TAllocType,int32 InitSize,class MutexType=CMutex>
class CMemAllocator
{
	public:
		CMemAllocator()
		{
			m_nInitSize = 0;
			m_pDataList = NULL;
			m_nInitSize = InitSize;

			__initMem();
		}
		virtual ~CMemAllocator()
		{
			
		}
	public:
		TAllocType* getFreeNode()
		{
			CGuard _gurad(m_mutex);

			if (!m_pDataList)
			{
				__reAlloc(m_nInitSize);
			}
			TAllocType* _retData = &m_pDataList->uNodeData.curNode;
			m_pDataList = m_pDataList->uNodeData.pNextNode;
			
			return _retData;
		}
		void freeNode(TAllocType* nodeData)
		{
			CGuard _gurad(m_mutex);

			memset(nodeData,0,sizeof(TAllocType));
			
			TNodeInfo* _nodeInfo = (TNodeInfo*)nodeData;
			_nodeInfo->uNodeData.pNextNode = m_pDataList;
			m_pDataList = (TNodeInfo*)nodeData;
		}
	private:
		void __initMem()
		{
			if (!m_pDataList)
			{
				__reAlloc(m_nInitSize);
			}
		}
		void __reAlloc(int32 allocSize)
		{
			void* _ptrData = malloc(allocSize * sizeof(TNodeInfo));
			if (!_ptrData)
				return;
			memset(_ptrData,0,sizeof(TNodeInfo) * allocSize);

			for (int32 _i = 0; _i < allocSize; _i++)
			{
				TNodeInfo* _nodePtr = (TNodeInfo*)((char*)_ptrData + sizeof(TNodeInfo) * _i);
				if (m_pDataList)
				{
					_nodePtr->uNodeData.pNextNode = m_pDataList;
					m_pDataList = _nodePtr;
				}
				else
				{
					m_pDataList = _nodePtr;	
				}
			}
		}
	private:
		struct TNodeInfo
		{
			union
			{
				TAllocType  curNode;
				TNodeInfo*  pNextNode;
			}uNodeData;
		};
	private:
		int32		m_nInitSize;
		TNodeInfo*	m_pDataList;
		MutexType	m_mutex;
};


/******************************************************************* 
 *  Copyright(c) 2000-2013 linghegu
 *  All rights reserved. 
 *  Author: 	wangbin
 *  Email:  	wang70bin@163.com
 *  CreateTime: 2014/4/15  
 ******************************************************************/
#pragma once

#include <stdlib.h>
#include <string.h>
#include "mutex.h"

template<class TAllocType,int InitSize,class MutexType>
class MemAllocator
{
	public:
		MemAllocator()
		{
			init_size_ = 0;
			ptr_data_list_ = NULL;
			init_size_ = InitSize;

			__init_mem();
		}
		virtual ~MemAllocator()
		{
			
		}
	public:
		TAllocType* get_free_node()
		{
			ScopeGuard scope_gurad(mutex_);

			if (!ptr_data_list_){
				__reAlloc(init_size_);
			}

			TAllocType* ret_ptr = &ptr_data_list_->nodedata.curNode;
			ptr_data_list_ = ptr_data_list_->nodedata.pNextNode;
			
			return ret_ptr;
		}
		void free_node(TAllocType* nodedata)
		{
			ScopeGuard scope_gurad(mutex_);

			memset(nodedata,0,sizeof(TAllocType));
			
			TNodeInfo* _nodeInfo = (TNodeInfo*)nodedata;
			_nodeInfo->uNodeData.pNextNode = ptr_data_list_;
			ptr_data_list_ = (TNodeInfo*)nodedata;
		}
	private:
		void __init_mem()
		{
			if (!ptr_data_list_){
				__reAlloc(init_size_);
			}
		}
		void __reAlloc(int allosize)
		{
			void* _ptrData = malloc(allosize * sizeof(TNodeInfo));
			if (!_ptrData)
				return;

			memset(_ptrData,0,sizeof(TNodeInfo) * allosize);
			for (int i = 0; i < allosize; i++) {
				TNodeInfo* _nodePtr = (TNodeInfo*)((char*)_ptrData + sizeof(TNodeInfo) * i);
				if (ptr_data_list_) {
					_nodePtr->nodedata.pNextNode = ptr_data_list_;
					ptr_data_list_ = _nodePtr;
				}
				else {
					ptr_data_list_ = _nodePtr;	
				}
			}
		}
	private:
		struct TNodeInfo{
			union{
				TAllocType  curNode;
				TNodeInfo*  pNextNode;
			}nodedata;
		};
	private:
		int			init_size_;
		TNodeInfo*	ptr_data_list_;
		MutexType	mutex_;
};


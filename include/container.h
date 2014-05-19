/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/05
******************************************************************/
#ifndef __INCLUDE_CONTAINER_H_
#define __INCLUDE_CONTAINER_H_

template<class T, int size>
class CircleQueue
{
	public:
		CircleQueue()
		{	
			cache_size_ = size;
			head_ = 0;
			tail_ = 0;	
			data_cache_ = new T[size];
		}

		~CircleQueue()
		{
			delete []data_cache_;
		}

		void pop(T& value)
		{
			int tmp_pos = (head_ + 1) % cache_size_;
			memcpy(&value,&data_cache_[tmp_pos],sizeof(T));
			head_ = tmp_pos;
		}

		void push(T& value)
		{	
			int tmp_pos = (tail_ + 1) % cache_size_;	
			memcpy(&data_cache_[push_pos_],&value,sizeof(T));
			tail_ = tmp_pos;
		}

		bool is_full() const
		{
			return ((tail_ + 1) % cache_size_) == head_;
		}

		bool is_empty() const
		{	
			return tail_ == head_;	
		}
		
	private:	
		T*	data_cache_;
		int cache_size_;
		int head_;
		int tail_;
};

#endif

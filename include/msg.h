/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#ifndef __INCLUDE_MSG_H_
#define __INCLUDE_MSG_H_
#pragma pack(1)

#include "networkdefine.h"

/*
 * Define the message head,all the message content will be appended from pointer of "data"
 * */
struct SMsgMetaData
{
	uint16	msgType;
	uint16	dataLen;
	char	data[0];
};



/*
 * Define the message type which only contain one send-content
 * */
template<class TDataInfoType>
class MessageMonoInfoTemplate
{
	public:
		void copy_data(const TDataInfoType* data)
		{
			memcpy(&data_,data,sizeof(TDataInfoType));
		}
		const void* get_data_ptr() const
		{
			return (void*)(data_);
		}
		int get_data_len() const
		{
			return sizeof(TDataInfoType);
		}
	private:
		TDataInfoType	data_;
};

/*
 * Define the message type which can contain multi-send-content
 * */
template<class TDataInfoType,int MaxScaleNum>
class MessageFlexInfoTemplate
{
	public:
		void resetData()
		{
			count_ = 0; 
		}
		void pushData(const TDataInfoType* copydata)
		{
			memcpy(&data_[count_++],copydata,sizeof(TDataInfoType));
		}
		const void* getDataPtr() const
		{
			return (void*)(&data_[0]);
		}
		int32 getDataLen() const
		{
			return count_ > 0 ? sizeof(TDataInfoType) * count_ : 0;
		}
	private:
		int				count_;			//
		TDataInfoType	data_[MaxScaleNum];
};

#pragma pcak()

#endif

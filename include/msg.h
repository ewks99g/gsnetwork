/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/28
******************************************************************/
#pragma once
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
class CMessageMonoInfoTemplate
{
	public:
		void copyData(const TDataInfoType* copydata)
		{
			memcpy(&m_data,copydata,sizeof(TDataInfoType));
		}
		const void* getDataPtr() const
		{
			return (void*)(m_data);
		}
		int32 getDataLen() const
		{
			return sizeof(TDataInfoType);
		}
	private:
		TDataInfoType	m_data;
};

/*
 * Define the message type which can contain multi-send-content
 * */
template<class TDataInfoType,int32 MaxScaleNum>
class CMessageFlexInfoTemplate
{
	public:
		void resetData()
		{
			m_nNumber = 0; 
		}
		void pushData(const TDataInfoType* copydata)
		{
			memcpy(&m_vData[m_nNumber++],copydata,sizeof(TDataInfoType));
		}
		const void* getDataPtr() const
		{
			return (void*)(&m_vData[0]);
		}
		int32 getDataLen() const
		{
			return m_nNumber > 0 ? sizeof(TDataInfoType) * m_nNumber : 0;
		}
	private:
		int32			m_nNumber;				//
		TDataInfoType	m_vData[MaxScaleNum];
};

#pragma pcak()

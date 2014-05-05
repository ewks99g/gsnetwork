/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/05
******************************************************************/
#pragma once
#include "networkdefine.h"

class CStream
{
	public:
		CStream();
		~CStream();

	public:
		void readRawData(char* data,int32 datalen);
	private:
		char	m_vRcvBuff[MAX_CONNCTOR_RCV_BUFF_SIZE];

		int32	m_nNeedBytes;					//needed bytes for next reading
		bool	m_bIsReadingHead;				//reading head or not
		int32	m_nRestBytes;					//rest data in readed buff
		int32	m_nMsgBuffOffset;				//msg buffset

};

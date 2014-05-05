/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/05
******************************************************************/
#include "stream.h"

CStream::CStream()
{
}

CStream::~CStream()
{
}

void CStream::readRawData(char* data,int32 datalen)
{
	m_nRestBytes = datalen;
	while (m_nRestBytes > 0)
	{
		if (m_nRestBytes < m_nNeedBytes) 
		{
			memcpy(m_vRcvBuff + m_nMsgBuffOffset, data + datalen - m_nRestBytes,m_nRestBytes);
			m_nMsgBuffOffset += m_nRestBytes;
			m_nNeedBytes -= m_nRestBytes;
			m_nRestBytes -= m_nRestBytes;
		}
		else
		{
			if (m_bIsReadingHead)
			{
				memcpy(m_vRcvBuff + m_nMsgBuffOffset, data + datalen - m_nRestBytes, m_nNeedBytes);
				m_nMsgBuffOffset += m_nNeedBytes;
				m_nRestBytes -= m_nNeedBytes;  
			//	SMessageStructure* _pHead = (SMessageStructure*)(&m_vRcvBuff[0]);
				//printf("handle rcv %d\n",_pHead->nMessageType);  
				m_bIsReadingHead = false; 
			//	m_nNeedBytes = _pHead->nByteSize;   
			}
			else
			{
				memcpy(m_vRcvBuff + m_nMsgBuffOffset, data + datalen - m_nRestBytes, m_nNeedBytes);
				m_nMsgBuffOffset += m_nNeedBytes;               
				m_nRestBytes -= m_nNeedBytes;
			
				//pushMsg(m_vRcvBuff, m_nMsgBuffOffset); 
				//
				m_nMsgBuffOffset = 0;        
				m_bIsReadingHead = true; 
		//		m_nNeedBytes = MESSAGE_HEAD_SIZE; 
		//		memset(m_vRcvBuff,0,MESSAGE_BLOCK_SIZE);   
			}
		}
	}
}

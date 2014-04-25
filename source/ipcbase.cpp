/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/17
******************************************************************/
#include "ipcbase.h"
#include "err.h"

CIpcBase::CIpcBase()
{
}

CIpcBase::~CIpcBase()
{
}

/*****************************************************************/
CSocketHandler::CSocketHandler()
{
	memset(&m_uAddress,0,sizeof(sockaddr_in));
}

CSocketHandler::~CSocketHandler()
{
}

void CSocketHandler::open(const char* ipstring,uint16 port)
{
	m_uAddress.sin_family = AF_INET;
	m_uAddress.sin_port = htons(port);
	if(inet_aton(ipstring,&m_uAddress.sin_addr) == 0)
	{
		output_error("Convert number-and-dots notation to number of network byte order");
		return;
	}

	m_nHandler = socket(PF_INET,SOCK_STREAM,0);
	if (m_nHandler < 0)
	{
		output_error("Create Socket");
		return;
	}

	if (connect(m_nHandler,(struct sockaddr*)&m_uAddress, sizeof(struct sockaddr_in)) < 0)
	{
		output_error("Can not connect the target server");
		return;
	}
	
	
}	

void CSocketHandler::inEvent()
{

}

void CSocketHandler::outEvent()
{

}

void CSocketHandler::timeEvent()
{

}

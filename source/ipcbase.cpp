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
CTcpConnector::CTcpConnector(CMultiplexContext* pcontext) : CIoEvent(pcontext)
{
	memset(&m_uAddress,0,sizeof(sockaddr_in));
}

CTcpConnector::~CTcpConnector()
{
}

bool CTcpConnector::open(const char* ipstring,uint16 port)
{
	m_uAddress.sin_family = AF_INET;
	m_uAddress.sin_port = htons(port);
	if(inet_aton(ipstring,&m_uAddress.sin_addr) == 0)
	{
		output_error("Convert number-and-dots notation to number of network byte order");
		return false;
	}

	m_nHandler = socket(PF_INET,SOCK_STREAM,0);
	if (m_nHandler < 0)
	{
		output_error("Create Socket");
		return false;
	}

	if (connect(m_nHandler,(struct sockaddr*)&m_uAddress, sizeof(struct sockaddr_in)) < 0)
	{
		output_error("Can not connect the target server");
		return false;
	}
	
	if (!m_pContext->addNetNode(this))
	{
		output_error("Can not connect the target server");
        return false;
	}


	return true;
}	

void CTcpConnector::inEvent()
{
	printf("rcv data\n");
}

void CTcpConnector::outEvent()
{

}

void CTcpConnector::errorEvent()
{

}

void CTcpConnector::timeEvent()
{

}
bool CTcpConnector::sendData(const char* data,uint32 len)
{
	if (data && len > 0)
	{
		int32 _sndLen = send(m_nHandler,data,len,0);
		if (_sndLen < len)
		{
			output_error("Send data error");
			return false;
		}
	}
	return true;
}
/**********************************************************************************************/
CTcpAcceptor::CTcpAcceptor(CMultiplexContext* pcontext) : CIoEvent(pcontext) 
{
}

CTcpAcceptor::~CTcpAcceptor()
{
}

bool CTcpAcceptor::open(const char* ipstring ,uint16 port)
{
	m_uAddress.sin_family = AF_INET;
    m_uAddress.sin_port = htons(port);
    if(inet_aton(ipstring,&m_uAddress.sin_addr) == 0)
    {
        output_error("Convert number-and-dots notation to number of network byte order");
        return false;
    }

    m_nHandler = socket(PF_INET,SOCK_STREAM,0);
    if (m_nHandler < 0)
    {
        output_error("Create Socket");
        return false;
    }

    if (bind(m_nHandler,(struct sockaddr*)&m_uAddress, sizeof(struct sockaddr_in)) < 0)
    {
        output_error("Can not connect the target server");
        return false;
    }

	if (listen(m_nHandler,MAX_INNER_PORT_LISTEN_BACK_LOG) < 0)
	{
		output_error("Can not listen on this socket");
		return false;
	}

	if (!m_pContext->addNetNode(this))
	{
		output_error("Can not add this node to multiplex way");
        return false;
	}

    return true;
}

void CTcpAcceptor::inEvent()
{
	THandler _rcvHandle = -1;
	struct sockaddr_in _remoteAddr;
	memset(&_remoteAddr,0,sizeof(struct sockaddr_in ));
	socklen_t _addrLen = sizeof(struct sockaddr_in);

	if (accept(m_nHandler,(struct sockaddr*)&_remoteAddr,&_addrLen) < 0)
	{
		output_error("Can not accept the comming connection request");
	}
	printf("Accept one comming request\n");
}

void CTcpAcceptor::outEvent()
{

}

void CTcpAcceptor::timeEvent()
{

}
void CTcpAcceptor::errorEvent()
{
	printf("rcbv error event\n");
}

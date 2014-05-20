/*******************************************************************
*  Copyright(c) 2000-2013 lingheg
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/04/17
******************************************************************/
#include "ipcbase.h"
#include "err.h"

IpcBase::IpcBase()
{
}

IpcBase::~IpcBase()
{
}

/*****************************************************************/
TcpConnector::TcpConnector(MultiplexContext* pcontext) : IoEvent(pcontext)
{
	memset(&address_,0,sizeof(sockaddr_in));
}

TcpConnector::~TcpConnector()
{
}

bool TcpConnector::open(const char* ipstring,uint16 port)
{
	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);
	if(inet_aton(ipstring,&address_.sin_addr) == 0)
	{
		output_error("Convert number-and-dots notation to number of network byte order");
		return false;
	}

	event_handler_ = socket(PF_INET,SOCK_STREAM,0);
	if (event_handler_ < 0)
	{
		output_error("Create Socket");
		return false;
	}

	if (connect(event_handler_,(struct sockaddr*)&address_, sizeof(struct sockaddr_in)) < 0)
	{
		output_error("Can not connect the target server");
		return false;
	}
	
	if (!context_->add_net_node(this,EPOLLIN))
	{
		output_error("Can not connect the target server");
        return false;
	}


	return true;
}	

void TcpConnector::in_event()
{
	printf("rcv data\n");
}

void TcpConnector::out_event()
{
	int32 _rcvLen = read(event_handler_,&m_vRcvBuff[0],MAX_CONNCTOR_RCV_BUFF_SIZE);
	
	if (_rcvLen > 0)
	{
		printf("prepare to handle data\n");
		return;
	}
	else 
	{
		if (!context_->rmv_net_node(this))
		{
			output_error("Can not rmv the connect event");
		}	
	}
}

void TcpConnector::error_event()
{
	printf("error event");
	if (!context_->rmv_net_node(this))
	{
		output_error("Can not rmv the connect event");
	}
}

void TcpConnector::time_event()
{

}
bool TcpConnector::sendData(const char* data,uint32 len)
{
	if (data && len > 0)
	{
		int32 _sndLen = send(event_handler_,data,len,0);
		if (_sndLen < len)
		{
			output_error("Send data error");
			return false;
		}
	}
	return true;
}
/**********************************************************************************************/
TcpAcceptor::TcpAcceptor(MultiplexContext* pcontext) : IoEvent(pcontext) 
{
}

TcpAcceptor::~TcpAcceptor()
{
}

bool TcpAcceptor::open(const char* ipstring ,uint16 port)
{
	address_.sin_family = AF_INET;
    address_.sin_port = htons(port);
    if(inet_aton(ipstring,&address_.sin_addr) == 0)
    {
        output_error("Convert number-and-dots notation to number of network byte order");
        return false;
    }

    event_handler_ = socket(PF_INET,SOCK_STREAM,0);
    if (event_handler_ < 0)
    {
        output_error("Create Socket");
        return false;
    }

    if (bind(event_handler_,(struct sockaddr*)&address_, sizeof(struct sockaddr_in)) < 0)
    {
        output_error("Can not connect the target server");
        return false;
    }

	if (listen(event_handler_,MAX_INNER_PORT_LISTEN_BACK_LOG) < 0)
	{
		output_error("Can not listen on this socket");
		return false;
	}

	if (!context_->add_net_node(this,EPOLLIN))
	{
		output_error("Can not add this node to multiplex way");
        return false;
	}

    return true;
}

void TcpAcceptor::in_event()
{
	THandler _rcvHandle = -1;
	struct sockaddr_in _remoteAddr;
	memset(&_remoteAddr,0,sizeof(struct sockaddr_in ));
	socklen_t _addrLen = sizeof(struct sockaddr_in);

	if (accept(event_handler_,(struct sockaddr*)&_remoteAddr,&_addrLen) < 0)
	{
		output_error("Can not accept the comming connection request");
	}
	printf("Accept one comming request\n");
}

void TcpAcceptor::out_event()
{

}

void TcpAcceptor::time_event()
{

}
void TcpAcceptor::error_event()
{
	printf("rcbv error event\n");
}

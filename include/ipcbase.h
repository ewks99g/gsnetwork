#pragma once
#include "networkdefine.h"
#include "ioevent.h"
#include "context.h"

class IpcBase
{
	public:
		IpcBase();
		virtual ~IpcBase();
};

//template<class TMsgHandler>
class TcpConnector : public IoEvent
{
	public:
		TcpConnector(MultiplexContext* pcontext);
		~TcpConnector();
	public:
		bool open(const char* ipstring,uint16 port);
		bool sendData(const char* data,uint32 len);
	public:
		virtual void in_event();
		virtual void out_event();
		virtual void error_event();
		virtual void time_event();
	private:
		char	m_vRcvBuff[MAX_CONNCTOR_RCV_BUFF_SIZE];
};

class TcpAcceptor : public IoEvent
{
	public:
		TcpAcceptor(MultiplexContext* pcontext);
		~TcpAcceptor();
	public:
		bool open(const char* ipstring,uint16 port);
	public:
		virtual void in_event();
		virtual void out_event();
		virtual void error_event();
		virtual void time_event();
};

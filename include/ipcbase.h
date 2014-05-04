#pragma once
#include "networkdefine.h"
#include "ioevent.h"
#include "context.h"

class CIpcBase
{
	public:
		CIpcBase();
		virtual ~CIpcBase();
};

//template<class TMsgHandler>
class CTcpConnector : public CIoEvent
{
	public:
		CTcpConnector(CMultiplexContext* pcontext);
		~CTcpConnector();
	public:
		bool open(const char* ipstring,uint16 port);
		bool sendData(const char* data,uint32 len);
	public:
		virtual void inEvent();
		virtual void outEvent();
		virtual void errorEvent();
		virtual void timeEvent();
	private:
		char	m_vRcvBuff[MAX_CONNCTOR_RCV_BUFF_SIZE];
};

class CTcpAcceptor : public CIoEvent
{
	public:
		CTcpAcceptor(CMultiplexContext* pcontext);
		~CTcpAcceptor();
	public:
		bool open(const char* ipstring,uint16 port);
	public:
		virtual void inEvent();
		virtual void outEvent();
		virtual void errorEvent();
		virtual void timeEvent();
};

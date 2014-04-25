#pragma once
#include "networkdefine.h"
#include "ioevent.h"

class CIpcbase
{
	public:
		CIpcbase(){}
		virtual ~CIpcbase(){}
};

//template<class TMsgHandler>
class CSocketHandler : public CIoEvent
{
	public:
		CSocketHandler();
		~CSocketHandler();
	public:
		void open(const char* ipstring,uint16 port);
	public:
		virtual void inEvent();
		virtual void outEevent();
		virtual void timeEevent();
	private:
		TMsgHandler		m_nHandler;
		struct sockaddr_in		m_uAddress;

//		NetIPv4			m_nIp;
//		NetPort			m_nPort;
};

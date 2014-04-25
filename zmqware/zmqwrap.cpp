/******************************************************************* 
*  Copyright(c) 2014-2017 linghegu
*  All rights reserved. 
*  Author:     wangbin
*  Email:      wang70bin@163.com
*  CreateTime: 2014/4/25  
******************************************************************/
#include "zmqwrap.h"

CZmqWrapper::CZmqWrapper(int threadnum) : m_context(threadnum)
{
	memset(&m_vPollItem[0],0,sizeof(m_vPollItem));
	m_nFreePollIndex = 0;
}

CZmqWrapper::~CZmqWrapper()
{

}

bool CZmqWrapper::init()
{
	return false;
}

bool CZmqWrapper::addBindNode(std::string ipcstring)
{
	zmq::socket_t* _pSocket = new zmq::socket_t(m_context,ZMQ_DEALER);
	if (!_pSocket)
	{	
		return false;
	}

	try
	{

		_pSocket->bind(ipcstring.c_str());

		m_vPollItem[m_nFreePollIndex].events = ZMQ_POLLIN;
		m_vPollItem[m_nFreePollIndex].socket = *_pSocket;
		m_vPollItem[m_nFreePollIndex].fd = 0;
		m_vPollItem[m_nFreePollIndex].revents = 0;

		m_nFreePollIndex++;

	}
	catch (zmq::error_t e)
	{
		printf("%s,%d,error %s\n",__FUNCTION__,__LINE__,e.what());
	}
	return true;
}

bool CZmqWrapper::addConNode(std::string ipcstring)
{
	zmq::socket_t* _pSocket = new zmq::socket_t(m_context,ZMQ_DEALER);
	if (!_pSocket)
	{	
		return false;
	}

	try
	{
		_pSocket->connect(ipcstring.c_str());

		m_vPollItem[m_nFreePollIndex].events = ZMQ_POLLIN;
		m_vPollItem[m_nFreePollIndex].socket = *_pSocket;
		m_vPollItem[m_nFreePollIndex].fd = 0;
		m_vPollItem[m_nFreePollIndex].revents = 0;

		m_nFreePollIndex++;
	}
	catch (zmq::error_t e)
	{
		printf("%s,%d,error %s\n",__FUNCTION__,__LINE__,e.what());
	}
	return true;
}


template<typename TMsgHandler>
void CZmqWrapper::run(TMsgHandler* msghandler)
{
	int _totalPollItem = m_nFreePollIndex;
	if (_totalPollItem == 0)
		return;

	while (true)
	{
		try
		{
			zmq::poll(m_vPollItem, _totalPollItem);

			for (int _i = 0; _i < _totalPollItem; _i++)
			{
				if (m_vPollItem [_i].revents & ZMQ_POLLIN) 
				{
					zmq::message_t _rcvMsg;
				//	(zmq::socket_t*)(m_vPollItem[_i].socket)->recv(_rcvMsg);

					printf("rcb msg \n");

			//		msghandler->process(_rcvMsg.data(),_rcvMsg.size());

			//		_rcvMsg.close();
				}
			}
		}
		catch(zmq::error_t e)
		{
			printf("%s,%d,error %s\n",__FUNCTION__,__LINE__,e.what());
		}
	}
}

void CZmqWrapper::run()
{
	int _totalPollItem = m_nFreePollIndex;
	if (_totalPollItem == 0)
		return;

	while (true)
	{
		try
		{
			zmq::poll(&m_vPollItem[0], _totalPollItem);

			for (int _i = 0; _i < _totalPollItem; _i++)
			{
				if (m_vPollItem [_i].revents & ZMQ_POLLIN) 
				{
					zmq::message_t _rcvMsg;
					_rcvMsg.rebuild();
					//((zmq::socket_t*)(m_vPollItem[_i].socket))->recv(&_rcvMsg);
					zmq_recv (m_vPollItem[_i].socket, &_rcvMsg, 0,0);

					printf("rcb msg \n");
				}
			}
		}
		catch(zmq::error_t e)
		{
			printf("%s,%d,error %s\n",__FUNCTION__,__LINE__,e.what());
		}
	}
}

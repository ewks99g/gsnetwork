/******************************************************************* 
*  Copyright(c) 2014-2017 linghegu
*  All rights reserved. 
*  Author:     wangbin
*  Email:      wang70bin@163.com
*  CreateTime: 2014/4/25  
******************************************************************/
#pragma once
#include <list>
#include "zmq.hpp"

#define MAX_ZMQ_THREAD_NUMBER 1
#define MAX_ZMQ_POLL_ITEM_NUMBER 10

class CZmqWrapper
{
public:
	explicit CZmqWrapper(int threadnum);
	~CZmqWrapper();
public:
	bool	init();
	bool	addBindNode(std::string ipcstring);
	bool	addConNode(std::string ipcstring);
public:
	template<typename TMsgHandler>
	void	run(TMsgHandler* msghandler);

	void	run();
private:
	zmq::context_t				m_context;
	std::list<zmq::socket_t>	m_vBindSocket;
	std::list<void*>			m_vConnSocket;

	zmq::pollitem_t				m_vPollItem[MAX_ZMQ_POLL_ITEM_NUMBER];
	int							m_nFreePollIndex;
};
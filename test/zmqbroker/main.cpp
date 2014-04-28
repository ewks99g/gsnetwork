#include "zmqwrap.h"
#include <iostream>

int main(int argc,char* argv[])
{
	CZmqWrapper _zmqwrap(MAX_ZMQ_THREAD_NUMBER);

	_zmqwrap.addBindNode("tcp://*:6001");
	_zmqwrap.addBindNode("tcp://*:6000");

	_zmqwrap.run();
}

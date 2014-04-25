#include "zmqwrap.h"
#include <iostream>
//
//int main(int argc,char* argv[])
//{
//	zmq::context_t  _context(1);
//	zmq::socket_t _socket(_context,ZMQ_DEALER);
//	_socket.bind("tcp://*:5555");
//
//	while (true)
//	{
//		zmq::message_t _msg;
//		
//		try
//		{
//			_socket.recv(&_msg);
//			std::cout << "Received Hello" << std::endl;
//		}
//		catch (zmq::error_t e)
//		{
//			printf("error\n",e.num());
//		}
//		//_msg.rebuild();
//	}
//}


int main(int argc,char* argv[])
{
	CZmqWrapper _zmqwrap(MAX_ZMQ_THREAD_NUMBER);

	_zmqwrap.addBindNode("tcp://*:5555");

	_zmqwrap.run();
}

//int main () {
//    // Prepare our context and socket
//    zmq::context_t context (1);
//    zmq::socket_t socket (context, ZMQ_REP);
//    socket.bind ("tcp://*:5555");
//
//    while (true) {
//        zmq::message_t request;
//
//        // Wait for next request from client
//        socket.recv (&request);
//        std::cout << "Received Hello" << std::endl;
//
//        // Do some 'work'
//        Sleep (1);
//
//        // Send reply back to client
//        zmq::message_t reply (5);
//        memcpy ((void *) reply.data (), "World", 5);
//        socket.send (reply);
//    }
//    return 0;
//}
#include "zmqwrap.h"

#include <stdio.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	void *context = zmq_init (1);

	// Socket to talk to server
	printf ("Connecting to hello world server¡­\n");
	void *requester = zmq_socket (context, ZMQ_DEALER);
	zmq_connect (requester, "tcp://localhost:5555");

	int request_nbr;
	for (request_nbr = 0; request_nbr != 100000; request_nbr++) {
		zmq_msg_t request;
		zmq_msg_init_size (&request, 5);
		memcpy (zmq_msg_data (&request), "Hello", 5);
		printf ("Sending Hello %d¡­\n", request_nbr);
		zmq_send (requester, &request, 0,0);
		zmq_msg_close (&request);

		usleep(1000);

		//zmq_msg_t reply;
		//zmq_msg_init (&reply);
		//zmq_recv (requester, &reply, 0,0);
		//printf ("Received World %d\n", request_nbr);
		//zmq_msg_close (&reply);
	}
	zmq_close (requester);
	zmq_term (context);
	return 0;
}


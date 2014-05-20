#include "context.h"
#include "ipcbase.h"

int main()
{
	MultiplexContext* _pCxt = new MultiplexContext();
	TcpConnector* _pConnector = new TcpConnector(_pCxt);
	_pConnector->open("127.0.0.1",9999);

	int _data = 4;
	_pConnector->sendData((const char*)&_data,sizeof(int));

//	_pCxt->addNetNode(_pAcceptor);
//
	_pCxt->start_run();

	while (1)
	sleep(1);
}

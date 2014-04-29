#include "context.h"
#include "ipcbase.h"

int main()
{
	CMultiplexContext* _pCxt = new CMultiplexContext();
	CTcpConnector* _pConnector = new CTcpConnector(_pCxt);
	_pConnector->open("127.0.0.1",9999);

	int _data = 4;
	_pConnector->sendData((const char*)&_data,sizeof(int));

//	_pCxt->addNetNode(_pAcceptor);
//
	_pCxt->startRun();

	while (1)
	sleep(1);
}

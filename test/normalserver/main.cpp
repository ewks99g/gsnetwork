#include "context.h"
#include "ipcbase.h"

int main()
{
	MultiplexContext* _pCxt = new MultiplexContext();
	TcpAcceptor* _pAcceptor = new TcpAcceptor(_pCxt);
	_pAcceptor->open("127.0.0.1",9999);

//	_pCxt->addNetNode(_pAcceptor);
//
	_pCxt->start_run();

	while (1)
	sleep(1);
}

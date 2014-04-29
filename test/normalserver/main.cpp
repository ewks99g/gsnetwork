#include "context.h"
#include "ipcbase.h"

int main()
{
	CMultiplexContext* _pCxt = new CMultiplexContext();
	CTcpAcceptor* _pAcceptor = new CTcpAcceptor(_pCxt);
	_pAcceptor->open("127.0.0.1",9999);

//	_pCxt->addNetNode(_pAcceptor);
//
	_pCxt->startRun();

	while (1)
	sleep(1);
}

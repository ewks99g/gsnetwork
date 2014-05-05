#include "memsys.h"
#include "mutex.h"
int
main()
{
	CMemAllocator<int,1000,CMutex> _allocator;
	
	for (int _i = 0; _i < 1000000000; _i++)
	{
	int* _val =_allocator.getFreeNode();
	//printf("%x\n",_val);
	}
}

#include "memsys.h"
#include "mutex.h"
int
main()
{
	MemAllocator<int,1000,Mutex> _allocator;
	
	for (int _i = 0; _i < 1000000000; _i++)
	{
	int* _val =_allocator.get_free_node();
	//printf("%x\n",_val);
	}
}

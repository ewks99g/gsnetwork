#include "head.h"
#include <stdio.h>

#pragma pack(1)
void testtemplatepush()
{
	printf("size is %d\n",sizeof(TestTemplatePush<int>));
}
#pragma pop()

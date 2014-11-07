#include "head.h"
#include <stdio.h>


void test_static_struct_new()
{
	static TTestStaticStructNew* test_value;

	printf("%x\n",test_value);
	if (test_value == NULL) {
		test_value = new TTestStaticStructNew;
	printf("%x\n",test_value);
	}
	
}

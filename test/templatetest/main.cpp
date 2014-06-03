/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include "test.inl"
#include <stdio.h>

void test_static_function_mem()
{
	static int test_function_static_mem;
	test_function_static_mem = 10;
	
//	static int test_function_static_mem = 10;
//	test_function_static_mem += 2;

	printf("static mem %d\n",test_function_static_mem);
}

void add_num(int val)
{
	val = val + 30;
}

int
main()
{
	FatherTemplate<int> _fatherclass(30);
	_fatherclass.dofunc();

	IntTemplate<30> _inttemplate;
	_inttemplate.dofunc();
	
	//do not pass type through<>
	template_func(30,&add_num);

	test_static_function_mem();
	test_static_function_mem();
}


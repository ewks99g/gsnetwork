/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include "test.inl"

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
}


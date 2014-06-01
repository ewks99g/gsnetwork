/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include <stdio.h>
//normal type test case
template<typename Typename>
class FatherTemplate
{
	public:
		FatherTemplate(Typename value)  {value_ = value;}
		virtual ~FatherTemplate(){}

		void dofunc() {printf("test template dofunc\n");}
	private:
		Typename value_;
};

//int type test case
template<int value>
class IntTemplate
{
	public:
		IntTemplate() {value_ = value;}
		virtual ~IntTemplate(){}

		void dofunc() {printf("test template dofunc\n");}
	private:
		int value_;
		
};

template<typename ValueType,typename FuncType>
void template_func(ValueType value,FuncType func)
{
	func(value);
}



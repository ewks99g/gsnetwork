/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include "test.inl"
#include <stdio.h>
#include "head.h"

void test_static_function_mem()
{
	static int test_function_static_mem;
	test_function_static_mem = 10;
	
//	static int test_function_static_mem = 10;
//	test_function_static_mem += 2;

	printf("static mem %d\n",test_function_static_mem);
}

template<>
void CDBCacheDataElem<int,int>::conditionRmv(int conditon)
{
        TElemMap::iterator _iter = m_vElems.begin();
        for (; _iter != m_vElems.end();_iter++)
        {   
//              if (_iter->first.nZoneType == conditon)
//              {
//                      m_vElems.erase(_iter++);
//              }
//              else
//              {
//                      _iter++;
//              }
        }                                                                                                                                                                                                      
}

template<>
void TestSpcial<SkillInfo,skillBaseInfo>::testFunc2() 
{

	     printf("testFunc int size %d\n", sizeof(TestTemplatePush<int>));
}

int
main()
{
	FatherTemplate<int> _fatherclass(30);
	_fatherclass.dofunc();

	IntTemplate<30> _inttemplate;
	_inttemplate.dofunc();
	
	test_static_function_mem();
	test_static_function_mem();

	SonNormalClass _sonclass;
	_sonclass.classTemplateFunction<int>();

	TestSpcial<SkillInfo,skillBaseInfo> _testsp1;
	_testsp1.testFunc1();
	_testsp1.testFunc2();

	testtemplatepush();

	CDBCacheDataElem<int,int> _cachedata;
	_cachedata.conditionRmv(2);

}


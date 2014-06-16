/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#include <map>
#include <stdio.h>
#include "head.h"
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


class NormalClass
{
	public:
	template<typename T>
	void classTemplateFunction()
	{
		printf("classTemplateFunction, father class\n");
	}
};

class SonNormalClass : public NormalClass
{
	public:
//	 template<typename T>
//	 void classTemplateFunction()
//	 {
//		 printf("classTemplateFunction, son class\n");
//	 }
};

struct SkillInfo
{
	int sid;
	int level;
};
struct skillBaseInfo
{
	int cd;
	int role;
};

/*test speclialization*/
template<typename T1,typename T2>
class TestSpcial
{
	public:
		void testFunc1();
		void testFunc2();
		
	protected:
	typedef std::map<T1,T2> TContainerMap;
	TContainerMap m_vMap;
};

template<>
void TestSpcial<SkillInfo,skillBaseInfo>::testFunc1() 
{

#pragma pack(1)
	 printf("testFunc int size %d\n", sizeof(TestTemplatePush<int>));
#pragma pop()
}

template<class T, class ELEM>
class CDBCacheDataElem
{
        typedef std::map<T,ELEM*> TElemMap;
public:
                void conditionRmv(int conditon);

private:
        TElemMap                                m_vElems;
        bool                                    m_bRRecvOk;                                             // 玩家当前拼包已经ok
};



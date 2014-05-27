/********************************************************************
	created:	2011/02/17
	created:	17:2:2011   15:58
	filename: 	inc\SqlDataReader.h
	file base:	SqlDataReader
	file ext:	h
	author:		zn
	fix:		wk
	
	purpose:	读取数据集合类，将数据操作接口传入类中，通过此类读取其中返回的数据
*********************************************************************/
#ifndef __SQL_DATA_READER_H__INCLUDE_
#define __SQL_DATA_READER_H__INCLUDE_
#include <stdlib.h>
#include "DBDefine.h"
#include "SqlCommand.h"

class CSqlDataReader
{
public:
	CSqlDataReader();
	CSqlDataReader(CSqlCommand* pInterface);
	~CSqlDataReader();

public:
	//读取整数
	template<class ParamType>
	bool getInt(int index, ParamType& returnValue)
	{
		if(m_Interface == NULL)
		{
			return false;
		}

		//m_Interface->nextRow();

		if(m_Interface->m_szRow == NULL)
		{
			return false;
		}

		if (m_Interface->m_szRow[index] == NULL)
		{
			return false;
		}

		returnValue = (ParamType)atoi(m_Interface->m_szRow[index]);

		return true;
	}

	//读取二进制内容
	bool				getBinary(int index, void* returnValue, int maxLen);
	//读取字符串
	bool				getString(int index, char* returnValue, int maxLen);
	//读取款字节
	bool				getStringW(int index, wchar_t* returnValue, int maxLen);
	//读取无符号整形
	bool				getUInt(int index, unsigned int& returnValue);

	//读取64整形
	bool				getUInt64(int index, db_uint64& returnValue);
	bool             getInt64(int index, db_int64& returnValue);
	//读取浮点数
	bool				getFloat(int index, float& returnValue);

	bool				fetchResult();

private:
	CSqlCommand*		m_Interface;
};

#endif

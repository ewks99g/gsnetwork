#include <string.h>
#include "SqlDataReader.h"
#include "DBUtil.h"


CSqlDataReader::CSqlDataReader()
{
}

CSqlDataReader::CSqlDataReader(CSqlCommand* pInterface)
{
	m_Interface = pInterface;
}

CSqlDataReader::~CSqlDataReader()
{
}

bool CSqlDataReader::getBinary(int index, void* returnValue, int maxLen)
{
	if(returnValue == NULL)
		return false;

	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		return false;
	}

	memcpy(returnValue, m_Interface->m_szRow[index], maxLen);

	return true;
}

bool CSqlDataReader::getString(int index, char* returnValue, int maxLen)
{
	if(returnValue == NULL)
		return false;

	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		return false;
	}

	size_t _nLen = strlen(m_Interface->m_szRow[index]);
	if(_nLen > size_t(maxLen - 1))
	{
		_nLen = maxLen - 1;
	}

	memcpy(returnValue, m_Interface->m_szRow[index], _nLen);
	return true;
}

bool CSqlDataReader::getStringW(int index, wchar_t* returnValue, int maxLen)
{
	if(returnValue == NULL)
		return false;

	char _MultiBuf[SQL_STR_LEN];
	memset(_MultiBuf, 0, SQL_STR_LEN);

	if(!getString(index, _MultiBuf, SQL_STR_LEN))
	{
		return false;
	}
	else
	{
		dTransForm::utf8_to_unicode(_MultiBuf, (db_int32)strlen(_MultiBuf), returnValue);
		return true;
	}	
}

bool CSqlDataReader::getUInt(int index, unsigned int& returnValue)
{
	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		return false;
	}

	returnValue = (unsigned int)atoi(m_Interface->m_szRow[index]);

	return true;
}

bool CSqlDataReader::getUInt64(int index, db_uint64& returnValue)
{
	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		returnValue = 0;
		return false;
	}
	
	returnValue = strtoull(m_Interface->m_szRow[index], (char **)NULL, 10);

	return true;
}

bool CSqlDataReader::getInt64(int index, db_int64& returnValue)
{
	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		returnValue = 0;
		return false;
	}

	returnValue = strtoull(m_Interface->m_szRow[index],(char **)NULL, 10);

	return true;
}

bool CSqlDataReader::getFloat(int index, float& returnValue)
{
	if(m_Interface == NULL)
	{
		return false;
	}

	if(m_Interface->m_szRow == NULL)
	{
		return false;
	}

	if (m_Interface->m_szRow[index] == NULL)
	{
		return false;
	}

	returnValue = float((atof(m_Interface->m_szRow[index])));

	return true;
}

bool CSqlDataReader::fetchResult()
{
	if(m_Interface == NULL)
		return false;

	m_Interface->nextRow();
	return true;
}

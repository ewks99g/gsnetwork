#include <string.h>
#include "SqlCommand.h"
#include "DBUtil.h"


static int sqlCmdCount = 0;

CSqlCommand::CSqlCommand()
	: m_bIsUse(false),
	m_bIsValid(false),
	m_pMySql(NULL),
	m_pRes(NULL),
	m_szRow(NULL),
	m_pStmt(NULL),
	m_nBindLen(0),
	m_nRowCount(0),
	m_nFieldCount(0),
	m_nAffectRow(0)
{

}

CSqlCommand::~CSqlCommand()
{

}

void CSqlCommand::clearBinaryParam(void)
{
	m_nBindLen = 0;
}

db_uint8 CSqlCommand::getBinaryParamNumber(void)
{
	return m_nBindLen;
}

bool CSqlCommand::addBinaryParam(EDBFieldTypes buf_type, void *buf, db_int32 buf_len)
{
	if (m_nBindLen < MAX_MYSQL_BIND_LEN)
	{
		memset(&m_bind[m_nBindLen], 0, sizeof(MYSQL_BIND));
		m_bind[m_nBindLen].buffer_type = (enum enum_field_types)buf_type;
		m_bind[m_nBindLen].buffer = buf;
		m_bind[m_nBindLen].buffer_length = buf_len;
		m_nBindLen++;
		return true;
	}

	return false;
}

db_int64 CSqlCommand::executeBinary(/*(*/char *sqlstr)	//这儿编译不过....改了一下——by：mm
{
	db_int32 _nBindLen = m_nBindLen;
	m_nBindLen = 0;

	if (sqlstr == NULL)
	{
		PRINTFERROR();
		return -1;
	}

	if (m_pMySql == NULL)
	{
		PRINTFERROR();
		m_bIsValid = false;
		return -1;
	}


	MYSQL_STMT  *m_pStmt = mysql_stmt_init(m_pMySql);
	if (m_pStmt == NULL)
	{
		MYSQLERROR(m_pMySql);
		m_bIsValid = false;
		return -1;
	}

	if (mysql_stmt_prepare(m_pStmt, sqlstr, (unsigned long)strlen(sqlstr)) != 0)  
	{		
		MYSQLSTMTERROR_SQL(m_pStmt, sqlstr);
		mysql_stmt_close(m_pStmt);
		m_pStmt = NULL;
		m_bIsValid = false;
		return -1;
	}	

	if (mysql_stmt_bind_param(m_pStmt, m_bind) != 0)
	{	
		MYSQLSTMTERROR_SQL(m_pStmt, sqlstr);
		mysql_stmt_close(m_pStmt);
		m_pStmt = NULL;
		m_bIsValid = false;
		return -1;
	}

	if (mysql_stmt_param_count(m_pStmt) != _nBindLen)
	{
		MYSQLSTMTERROR_SQL(m_pStmt, sqlstr);
		mysql_stmt_close(m_pStmt);
		m_pStmt = NULL;
		m_bIsValid = false;
		return -1;
	}

	int err = -1;
	if ((err = mysql_stmt_execute(m_pStmt)) != 0) 
	{
		MYSQLSTMTERROR_SQL(m_pStmt, sqlstr);		
		mysql_stmt_close(m_pStmt);
		m_pStmt = NULL;	

		if(err == 1) // sql执行失败
		{
			if (mysql_ping(m_pMySql) != 0)
			{
				m_bIsValid = false;				
			}
		}

		// err > 1 需要重新连接
		else
		{
			m_bIsValid = false;	
		}
		
		return -1;
	}

	m_nValue = (db_int32)mysql_stmt_affected_rows(m_pStmt);

	mysql_stmt_close(m_pStmt);
	m_pStmt = NULL;
	return m_nValue;
}

db_int64 CSqlCommand::executeBinaryW(wchar_t* sqlstr)
{
	if(sqlstr == NULL)
	{
		return -1;
	}

	char _MultiBuf[SQL_STR_LEN];
	memset(_MultiBuf, 0, SQL_STR_LEN);
	dTransForm::unicode_to_utf8(sqlstr, (db_int32)wcslen(sqlstr), _MultiBuf);

	return executeBinary(_MultiBuf);
}

db_int64 CSqlCommand::execute(char *sqlstr)
{
	if (sqlstr == NULL || sqlstr == "")
	{
		PRINTFERROR();
		return -1;
	}

	if (m_pMySql == NULL)
	{
		PRINTFERROR();
		m_bIsValid = false;
		return -1;
	}
	
	int err = -1;
	if ((err = mysql_real_query(m_pMySql, sqlstr, (db_uint32)strlen(sqlstr))) != 0)
	{
		MYSQLERROR_SQL(m_pMySql, sqlstr);
		freeRecord();

		if(err == 1) // sql执行失败
		{
			if (mysql_ping(m_pMySql) != 0)
			{
				m_bIsValid = false;				
			}
		}

		// err > 1 需要重新连接
		else
		{
			m_bIsValid = false;	
		}	
		const char *err_str = mysql_error(m_pMySql);
		printf("Sql execute error %s\n",err_str);
		return -1;
	}

	freeRecord();
	m_pRes = mysql_store_result(m_pMySql);
	if (m_pRes)
	{
		m_nRowCount = (db_int32)mysql_num_rows(m_pRes);
		m_nFieldCount = (db_int32)mysql_num_fields(m_pRes);
		m_nAffectRow = (db_int32)mysql_affected_rows(m_pMySql);
	}


	return (db_int64)mysql_affected_rows(m_pMySql);
}

db_int64 CSqlCommand::executeW(wchar_t* sqlstr)
{
	if(sqlstr == NULL)
		return 0;

	char _MultiBuf[SQL_STR_LEN];
	memset(_MultiBuf, 0, SQL_STR_LEN);
	dTransForm::unicode_to_utf8(sqlstr, (db_int32)wcslen(sqlstr), _MultiBuf);

	return execute(_MultiBuf);
}

bool CSqlCommand::connect(char *host, char *use, char *passwd, char *db, db_uint16 nPort)
{
	if (m_bIsValid)
	{
		return true;	
	}

	if (m_pMySql)
	{
		if (mysql_ping(m_pMySql) == 0)
		{
			m_bIsValid = true;
			return true;
		}

		close();
	}
	
	m_pMySql = mysql_init(NULL);
	if (m_pMySql == NULL)
	{
		return false;
	}

	//char value = 1;
	//mysql_options(m_pMySql, MYSQL_OPT_RECONNECT, (char*)&value); // 设置MYSQL_OPT_RECONNECT 为1，开启自动重连
	//mysql_options(m_pMySql, MYSQL_SET_CLIENT_IP, "10.221.152.156");
	

	if (mysql_real_connect(m_pMySql, host, use, passwd, db, nPort, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_INTERACTIVE))
	{
		if(mysql_set_character_set(m_pMySql, "utf8") != 0)
		{
			MYSQLERROR(m_pMySql);
			close();
			return false;
		}

		//if (mysql_query(m_pMySql, "SET sql_mode='NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION'") != 0)
		//{
		//	MYSQLERROR(m_pMySql);
		//	close();
		//	return false;
		//}

		m_bIsValid = true;
		return true;

	}
	else
	{
		MYSQLERROR(m_pMySql);
		return false;
	}

	return false;
}

void CSqlCommand::restore()
{
	freeRecord();
	clearBinaryParam();
	m_bIsUse = false;
}

void CSqlCommand::close()
{
	freeRecord();
	if (m_pMySql)
	{
		mysql_close(m_pMySql);
		m_pMySql = NULL;
		mysql_library_end(); // 使用mysql_real_connect之后，断开连接必须要，否则有可能内存泄露
	}
}

void CSqlCommand::freeRecord()
{
	if (m_pStmt)
	{
		mysql_stmt_close(m_pStmt);
		m_pStmt = NULL;
	}

	if (m_pRes)
	{
		mysql_free_result(m_pRes);
		m_nRowCount = 0;
		m_nFieldCount = 0;
		m_nAffectRow = 0;
		m_szRow = NULL;
		m_pRes = NULL;
	}
}

void CSqlCommand::nextRow()
{
	if (NULL == m_pRes)
	{
		return ;
	}

	m_szRow = mysql_fetch_row(m_pRes);
}


//主要功能:开始事务
void CSqlCommand::TransBegin()
{
	execute("SET AUTOCOMMIT=0");
	execute("START TRANSACTION");	
}
void CSqlCommand::TransBeginAuto()
{
	execute("SET AUTOCOMMIT=1");
	execute("START TRANSACTION");	
}
//-----------------------------------------------------------------------

/*
主要功能:提交事务
*/
void CSqlCommand::TransCommit()
{
	execute("COMMIT");
	execute("SET AUTOCOMMIT=1");

}
//--------------------------------------------------------------------------
/*
主要功能:回滚事务
*/
void CSqlCommand::TransRollback()
{
	execute("ROLLBACK");
	execute("SET AUTOCOMMIT=1");
};

/********************************************************************
	created:	2011/02/17
	created:	17:2:2011   15:58
	filename: 	d:\code\Server\Tool\MysqlDBInterface\inc\SqlCommand.h
	file path:	d:\code\Server\Tool\MysqlDBInterface\inc
	file base:	SqlCommand
	file ext:	h
	author:		zn
	fix:		wk

	purpose:	数据库执行接口，Sql语句执行时调用这个类
*********************************************************************/
#pragma once

#include "DBDefine.h"

#define MAX_MYSQL_BIND_LEN 20

enum EDBFieldTypes
{
	DB_TYPE_DECIMAL, 
	DB_TYPE_TINY,
	DB_TYPE_SHORT,  
	DB_TYPE_LONG,
	DB_TYPE_FLOAT,  
	DB_TYPE_DOUBLE,
	DB_TYPE_NULL,   
	DB_TYPE_TIMESTAMP,
	DB_TYPE_LONGLONG,
	DB_TYPE_INT24,
	DB_TYPE_DATE,   
	DB_TYPE_TIME,
	DB_TYPE_DATETIME, 
	DB_TYPE_YEAR,
	DB_TYPE_NEWDATE, 
	DB_TYPE_VARCHAR,
	DB_TYPE_BIT,
	DB_TYPE_NEWDECIMAL=246,
	DB_TYPE_ENUM=247,
	DB_TYPE_SET=248,
	DB_TYPE_TINY_BLOB=249,
	DB_TYPE_MEDIUM_BLOB=250,
	DB_TYPE_LONG_BLOB=251,
	DB_TYPE_BLOB=252,
	DB_TYPE_VAR_STRING=253,
	DB_TYPE_STRING=254,
	DB_TYPE_GEOMETRY=255,
	DB_TYPE_BINARY = DB_TYPE_TINY_BLOB,
};

class CSqlCommand
{
	friend class CDBManager;
	friend class CSqlDataReader;

public:
	//添加二进制内容时需要先调用这个接口把数据清零
	void					clearBinaryParam(void);
	db_uint8				getBinaryParamNumber(void);
	//添加二进制数据块
	bool					addBinaryParam(EDBFieldTypes ebuf_type, void *buf, db_int32 buf_len);
	//添加二进制数据块时需要调用这个接口
	db_int64				executeBinary(char *sqlstr);

	db_int64				executeBinaryW(wchar_t* sqlstr);
	//执行sql语句
	db_int64				execute(char *sqlstr);
	//执行sql语句款字节
	db_int64				executeW(wchar_t* sqlstr);
	
	void					restore();
	bool					isValid() { return m_bIsValid; }
	void					use() { m_bIsUse = true; };
	bool					isUse() { return m_bIsUse; }
	void					close();
	void					freeRecord();
	void					nextRow();
	bool					connect(char *host, char *use, char *passwd, char *db, db_uint16 nPort);
	db_int32				getRowNum() { return m_nRowCount;};
	db_int32                getAffecteRow() { return m_nAffectRow; }

	// 事务处理
	void TransBegin();	
	void TransBeginAuto();
	void TransCommit();
	void TransRollback();

private:
	bool					m_bIsValid;
	bool					m_bIsUse;
	MYSQL*					m_pMySql;
	MYSQL_RES*				m_pRes;						///结果集
	MYSQL_ROW				m_szRow;						    ///记录集
	MYSQL_STMT*				m_pStmt;
	db_int32				m_nRowCount;
	db_int32				m_nFieldCount; 
	db_int32                m_nAffectRow;

	
	MYSQL_BIND				m_bind[MAX_MYSQL_BIND_LEN];
	db_uint8				m_nBindLen;	
	db_int64				m_nValue;
	
private:
	CSqlCommand();
	~CSqlCommand();
};

class CSqlCmdBox
{
public:
	CSqlCmdBox(CSqlCommand* pCmd) : m_pCmd(pCmd) {};
	~CSqlCmdBox() { m_pCmd->restore(); }
private:
	CSqlCommand*	m_pCmd;
};


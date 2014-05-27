/********************************************************************
	created:	2011/02/17
	created:	17:2:2011   15:58
	filename: 	inc\DBManager.h
	file base:	DBManager
	file ext:	h
	author:		zn
	fix:		wangkai
	purpose:	
*********************************************************************/
#ifndef __DBMANAGER_H__INCLUDE_
#define __DBMANAGER_H__INCLUDE_

#include "SqlCommand.h"
#include "SqlDataReader.h"
#include "DBUtil.h"

const unsigned int MAX_CONN_LIMIT = 100; 

class CDBManager : private dThread
{
public:
	static CDBManager*				instance();

	//初始化 建立数据连接
	bool							init(char *host, char *use, char *passwd, char *db, db_uint16 nPort, db_uint8 connLimit);
	//取得数据库操作句柄
	CSqlCommand*					getSqlCommand();
	virtual db_uint32				run(){	return process(); }

private:
	CDBManager();
	~CDBManager();

	int								process();

private:
	bool							m_bIsInited;	//是否已经初始化了
	//static CDBManager*				m_pDBManager;
	CSqlCommand*					m_pCmdPool[MAX_CONN_LIMIT];
	int								m_nConnLimit;	//最多数据库连接数
	static int						m_nCurrIndex;		// 轮询SqlCommand用

	char							m_szHost[MAX_DB_HOST_NAME_LEN + 1];
	char							m_szUse[MAX_DB_USE_NAME_LEN + 1];
	char							m_szPwd[MAX_DB_PASSWD_LEN + 1];
	char							m_szDB[MAX_DB_DB_LEN + 1];
	db_uint16						m_nPort;
	dMutex							m_QueryMutex;
};

#define DBManager() CDBManager::instance()

//#define DEFAULT_SQL_INIT(fail) CSqlCommand *pCommand = DBManager()->getSqlCommand();if (!pCommand){ return fail;	}\
//	CSqlCmdBox border(pCommand); char sqlstr[SQL_STR_LEN]; memset(sqlstr, 0, SQL_STR_LEN);

#define DEFAULT_SQL_INIT_NORETURN() CSqlCommand *pCommand = DBManager()->getSqlCommand();if (!pCommand){ return;	}\
	CSqlCmdBox border(pCommand); char sqlstr[SQL_STR_LEN]; memset(sqlstr, 0, SQL_STR_LEN);

#define DEFAULT_SQL_INIT_RETURN() CSqlCommand *pCommand = DBManager()->getSqlCommand();if (!pCommand){ return INVAILD_LOAD_DB;	}\
	CSqlCmdBox border(pCommand); char sqlstr[SQL_STR_LEN]; memset(sqlstr, 0, SQL_STR_LEN);

#define DEFAULT_SQL_INIT_RETURN_BOOL() CSqlCommand *pCommand = DBManager()->getSqlCommand();if (!pCommand){ return false;	}\
	CSqlCmdBox border(pCommand); char sqlstr[SQL_STR_LEN]; memset(sqlstr, 0, SQL_STR_LEN);

#define DEFALUT_SQL_COMMAND_FREE() if (pCommand) { pCommand->restore(); }

#endif

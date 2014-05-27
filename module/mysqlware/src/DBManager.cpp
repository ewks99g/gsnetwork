#include <string.h>
#include <stdio.h>
#include "DBManager.h"
//CDBManager* CDBManager::m_pDBManager = NULL;
int CDBManager::m_nCurrIndex = 0;

CDBManager::CDBManager()
{
	m_nConnLimit = 0;
	memset(m_pCmdPool, 0, sizeof(m_pCmdPool));
	m_szHost[0]= '\0';
	m_szUse[0]= '\0';
	m_szPwd[0]= '\0';
	m_szDB[0]= '\0';
	m_nPort = 0;
	m_bIsInited = false;	
}

CDBManager::~CDBManager()
{
	for (int i = 0; i < m_nConnLimit; i++)
	{
		if (m_pCmdPool[i] != NULL)
		{
			m_pCmdPool[i]->close();
			delete m_pCmdPool[i];
			m_pCmdPool[i] = NULL;
		}
	}
}

CDBManager* CDBManager::instance()
{
	static CDBManager dbmr;

	return &dbmr;
}


bool CDBManager::init(char *host, char *use, char *passwd, char *db, db_uint16 nPort, db_uint8 connLimit)
{
	if (host)
	{
		strncpy(m_szHost, host, MAX_DB_HOST_NAME_LEN);
		m_szHost[MAX_DB_HOST_NAME_LEN] = '\0';		
	}

	if (use)
	{
		strncpy(m_szUse, use, MAX_DB_USE_NAME_LEN);
		m_szUse[MAX_DB_USE_NAME_LEN] = '\0';		
	}

	if (passwd)
	{
		strncpy(m_szPwd, passwd, MAX_DB_PASSWD_LEN);
		m_szPwd[MAX_DB_PASSWD_LEN] = '\0';
	}

	if (db)
	{
		strncpy(m_szDB, db, MAX_DB_DB_LEN);
		m_szDB[MAX_DB_DB_LEN] = '\0';		
	}
	m_nPort = nPort;
	m_nConnLimit = connLimit < MAX_DB_CONNECT_COUNT ? connLimit : MAX_DB_CONNECT_COUNT;

	for (int i = 0; i < m_nConnLimit; i++)
	{
		CSqlCommand *pSqlCmd = new CSqlCommand();
		if (pSqlCmd->connect(m_szHost, m_szUse, m_szPwd, m_szDB, m_nPort))
		{
			m_pCmdPool[i] = pSqlCmd;
		}
		else
		{
			for (int j = 0; j < m_nConnLimit; j++)
			{
				if (m_pCmdPool[j] != NULL)
				{
					delete m_pCmdPool[j];
				}
			}
			return false;
		}

		usleep(1000);
	}

	start(); //启动辅助线程

	m_bIsInited = true;
	return true;
}

CSqlCommand* CDBManager::getSqlCommand()
{
	//临界区保护
	dMutexGuard lock(m_QueryMutex);
	{		
		// 加入轮询机制，循环的目的是如果当前不可用，查找可用连接
		for (int i = 0; i < m_nConnLimit; i++)
		{
			assert(m_pCmdPool[m_nCurrIndex] != NULL);
			if (!m_pCmdPool[m_nCurrIndex]->isUse() && m_pCmdPool[m_nCurrIndex]->isValid())
			{
				//printf("m_pCmdPool[%d]\n", m_nCurrIndex);
				m_pCmdPool[m_nCurrIndex]->use();							

				CSqlCommand* _pSqlCommand = m_pCmdPool[m_nCurrIndex];
				m_nCurrIndex = (m_nCurrIndex+1 >= m_nConnLimit) ? 0 : (m_nCurrIndex+1);

				return _pSqlCommand;
			}
			
			m_nCurrIndex = (m_nCurrIndex+1 >= m_nConnLimit) ? 0 : (m_nCurrIndex+1);			
		}
	}

	printf("getSqlCommand NULL\n");
	//Util::sleep(1000);
	return NULL;
}

int CDBManager::process()
{
	while (true)
	{
		for (int i = 0; i < m_nConnLimit; i++)
		{
			assert(m_pCmdPool[i] != NULL);
			if (!m_pCmdPool[i]->isValid())
			{
				//m_pCmdPool[i]->connect(m_szHost, m_szUse, m_szPwd, m_szDB, m_nPort);
			}
		}
#ifdef WIN32
		::Sleep(10000);	//10秒执行一次
#elif LINUX
		usleep(10000000);
#endif
	}
	return 0;
}


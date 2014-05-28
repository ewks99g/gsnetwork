/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/28
******************************************************************/
#include "connectionpool.h"
#include "dbconnection.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	while (!db_conn_pool_.empty())
	{
		DBConnection* ptr_conn = db_conn_pool_.front(); 
		db_conn_pool_.pop();

		delete ptr_conn;
	}
}

bool DBConnectionPool::init_pool(int conn_num,const char* address,bool autoreconn,int wrtimeoutsec)
{
	if (conn_num <= 0 || address == NULL)
		return false;

	for (int i = 0; i < conn_num; i++) {
		DBConnection* ptr_conn = new DBConnection(autoreconn,wrtimeoutsec);
		if (NULL == ptr_conn) 
			return false;

		if (!ptr_conn->connect(address))
			return false;
	}
	return true;
}

DBConnection* DBConnectionPool::get_free_connection()
{
	if (db_conn_pool_.size() > 0) {
		DBConnection* ptr_conn = db_conn_pool_.front(); 
		db_conn_pool_.pop();

		return ptr_conn;
	}

	return NULL;
}

void DBConnectionPool::recycle_connection(DBConnection* con)
{
	if (con) {
		db_conn_pool_.push(con);
	}
}

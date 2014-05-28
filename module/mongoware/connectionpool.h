/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/28
******************************************************************/
#ifndef __MODULE_MONGOSWARE_CONNECTION_POOL_H__
#define __MODULE_MONGOSWARE_CONNECTION_POOL_H__

#include <queue>
#include "mongodef.h"

class DBConnection;
class DBConnectionPool
{
	public:
		DBConnectionPool();
		~DBConnectionPool();
	public:
		/*
		 *@conn_num: the number of connection in this poll
		 *@address: like 127.0.0.1 , 127.0.0.1:5555
		 *@autoreconn: auto reconnect
		 *@wrtimeoutsec: timeout of write/read
		 * */
		bool init_pool(int conn_num,const char* address,bool autoreconn,int wrtimeoutsec); 

		DBConnection* get_free_connection();
		void		  recycle_connection(DBConnection* con);
		
	private:
		std::queue<DBConnection*> db_conn_pool_;
};



#endif

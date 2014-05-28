/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	pengpeng
*  CreateTime: 2014/05/28
******************************************************************/
#ifndef __MONGOSWARE_MONGO_H__
#define __MONGOSWARE_MONGO_H__

#include <iostream>
#include <cstdlib>
#include <string.h>
#include "mongo/client/dbclient.h"
#include "mongodef.h"

/*
 * Implement one instance inherit from mongo-driver's connection base class
 *
 *
 * */
class DBConnection : public mongo::DBClientConnection
{
public:
	/**
	 *
	 *@autoreconn: autoreconn if true, automatically reconnect on a connection failure
	 *@wrtimeoutsec: timeout in second,when write/read
	 *
	 **/
	DBConnection(bool autoreconn,int wrtimeoutsec);
	virtual ~DBConnection();

public:
	/*
	 *in mongo,we usually only authorize the db "admin", then we open the door of god,else we need knock every door
	 *
	 *pwd: in plain txt,not digest
	 * */
	bool authorize(const char* user,const char* pwd,const char* dbname);

	/*
	 *Ends the current authentication session. 
	 *This function has no effect if the current session is not authenticated
	 * */
	virtual bool logout(const char* dbname);
	
	bool repairDatabase(const char* dbname);
	bool createCollection(const char* ns);
	bool dropCollection(const char* ns);

	bool excuteCmd(const char* dbname,const char* strcmd);
	
	/*
	 *start to connect 127.0.0.1 127.0.0.1:8088
	 * */
	virtual bool connect(const char* hostname);
	
	/*
	 *Debug method, used to view all the data in collection of "ns"
	 * */
	void printAll(const char* ns);
	
	/*
	 *simple insert method
	 * */
	virtual void insert(const char* ns,const std::vector<mongo::BSONObj>& bovec);
	
	/*
	 * simple remove method
	 * */
	virtual	void remove(const char* ns, const mongo::BSONObj& condition);

	/*
	 *ns: collection space/name
	 *result: the find result
	 *number: try to read number,if not enough,insert the max number
	 *
	 * */
	virtual void find(const char* ns,const mongo::BSONObj& condition,std::vector<mongo::BSONObj>& result,int number);
	
	/*
	 *condition: update conditon
	 *bo:		 update object
	 * */
	virtual bool update(const char* ns, const mongo::BSONObj& condition,const mongo::BSONObj& bo);
	
private:
	/// some monitor data,waiting 
};

#endif


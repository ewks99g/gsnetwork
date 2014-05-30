/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  CreateTime: 2014/05/28
 ******************************************************************/
#include "dbconnection.h"

DBConnection::DBConnection(bool autoreconn,int wrtimeoutsec)  : DBClientConnection(autoreconn,0,wrtimeoutsec)
{
}

DBConnection::~DBConnection()
{
	// to be continued
}

bool DBConnection::connect(const char* hostname)
{
	std::string errmsg;
	if (!DBClientConnection::connect(hostname,errmsg)) {
		fprintf(stderr,"Connect MongoDB: %s, error: %s",errmsg.c_str());
		return false;
	}

	return true;
}

bool DBConnection::createCollection(const char* ns)
{
	if (exists(ns))
		return false;

	if (!createCollection(ns)) {
		fprintf(stderr,"Can not Create Collection: %s",ns);
		return false;
	}
	return true;
}

bool DBConnection::dropCollection(const char* ns)
{
	if (!exists(ns))
		return false;

	if (!dropCollection(ns)) {
		fprintf(stderr,"Can not Drop Collection: %s",ns);
		return false;
	}   
	return true;
}

bool DBConnection::repairDatabase(const char* dbname)
{
	// I hope that i never use this in my life
}

bool DBConnection::authorize(const char* user,const char* pwd,const char* dbname) 
{
	std::string errmsg;
	if (!auth(std::string(dbname),std::string(user),std::string(pwd),errmsg)) {
		fprintf(stderr,"%s try to autorize : %s use %s, error: %s",user,dbname,pwd,errmsg.c_str());
        return false;
    }   
    return true;
}

bool DBConnection::logout(const char* dbname)
{
	//in case ,we will excute this guy
	mongo::BSONObj logoutword;
	DBClientConnection::logout(dbname,logoutword);
}

bool DBConnection::excuteCmd(const char* dbname,const char* strcmd)
{	
	if (!dbname || !strcmd)
		return false;

	mongo::BSONObj result;
	if (!runCommand(dbname,mongo::BSONObj(strcmd),result)) {
		fprintf(stderr,"Can not excute cmd %s in %s\n",strcmd,dbname);
		return false;
	}

	return true;
}

void DBConnection::printAll(const char* ns) 
{
	mongo::Query empty_query;
	std::auto_ptr<mongo::DBClientCursor> cursor = query(ns, empty_query);

	while (cursor.get() != NULL && cursor->more()) {
		mongo::BSONObj res = cursor->next();
		printf("%s\n",res.jsonString());
	}
}

void DBConnection::remove(const char* ns, const mongo::BSONObj& condition)
{
	mongo::Query query(condition);
	DBClientConnection::remove(ns,query);

	std::string strerr = getLastError();
	if (!strerr.empty()) {
		fprintf(stderr,"remove from %s,condition is %s\n",ns,condition.toString().c_str());
	}
}

void DBConnection::insert(const char* ns,const std::vector<mongo::BSONObj>& bovec)
{
	DBClientConnection::insert(ns, bovec);
	std::string strerr = getLastError();
	if (!strerr.empty()) {
		fprintf(stderr,"insert %s error\n",ns);
	}
}

bool DBConnection::update(const char* ns, const mongo::BSONObj& condition,const mongo::BSONObj& bo)
{
	DBClientConnection::update(ns,condition,bo);
	std::string strerr = getLastError();
	if (!strerr.empty()) {
		fprintf(stderr,"update %s,condition %s,bson %s\n",ns,condition.toString().c_str(),bo.toString().c_str());
	}
}

void DBConnection::find(const char* ns,const mongo::BSONObj& condition,std::vector<mongo::BSONObj>& result,int number)
{
	if (number <= 0)
		return;

	mongo::Query query_condition(condition);
	std::auto_ptr<mongo::DBClientCursor> cursor = query(ns, query_condition);
	
	int rd_count = 0;
	while (cursor.get() != NULL && cursor->more() && rd_count < number) {
		mongo::BSONObj bo = cursor->next();
		result.push_back(bo);
	}
}

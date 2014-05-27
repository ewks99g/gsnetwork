#ifndef __MONGOSWARE_MONGO_H__
#define __MONGOSWARE_MONGO_H__

#include <iostream>
#include <cstdlib>
#include <string.h>
#include "mongo/client/dbclient.h"
#include "mongodef.h"
using namespace std;
using namespace mongo;
using namespace bson;

class MongoInstance {
private:
	mongo::DBClientConnection conn;

public:
	MongoInstance();
	
	bool update(const char * ns, bo & file_od, bo & file_nw);
	
	void show(const char * ns);

	template <class T>
	void find_One(const string space = "", 
				  const string key = "", const T value = "");

	void Find(const string space = NULL);

	template <class T>
	void Remove(const string space = "", 
				const string key = "", const T value = false);

	void Remove(const char * space);

	template <class T>
	void Insert(const string space = "", const string key = "", 
				const T value = "");

	template <class T>
	void Update(const char * collname, const char * key, const T value,  
				const char * ud_key, const T ud_value, bool isSet);

	void Update(const char * collectName, BSONObj & res, BSONObj & obj);

	void op();
};



#endif

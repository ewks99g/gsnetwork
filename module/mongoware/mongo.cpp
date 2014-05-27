#include "mongo.h"

MongoInstance::MongoInstance() {
	conn.connect(string("127.0.0.1:") + "27017");
	cout << "connect ok" << endl;
}

bool MongoInstance::update(const char * ns, 
			bo & file_od, 
			bo & file_nw) {
	conn.update(ns, file_od, file_nw, false, true);

	string e = conn.getLastError();
	if ( !e.empty() ) {
		cout << "failed to update : " << e << endl;
		return false;
	}

	return true;
}

void MongoInstance::show(const char * ns) {
	std::auto_ptr<DBClientCursor> cursor = conn.query(ns, BSONObj());
	if ( cursor.get() == NULL ) {
		return ;
	}
	else {
		while ( cursor->more() ) {
			BSONObj res = cursor->next();
			cout << "\t" << res.jsonString() << endl;
		}
	}
}

template <class T>
void MongoInstance::find_One(const string space, 
		const string key, const T value) {
	mongo::BSONObjBuilder query;
	query.append(key, value);
	mongo::BSONObj res = conn.findOne(space, query.obj());
	cout << res.isEmpty() << "\t" << res.jsonString() << endl;
}

void MongoInstance::Find(const string space) {
	mongo::BSONObjBuilder query;
	std::auto_ptr<DBClientCursor> cursor = conn.query(space, query.obj());
	if ( cursor.get() == NULL ) {
		cout << "couldn't use cursor" << endl;
		exit(EXIT_FAILURE);
	}

	while ( cursor->more() ) {
		mongo::BSONObj res = cursor->next();
		cout << res.isEmpty() << "\t" << res.jsonString() << endl;
	}
}

template <class T>
void MongoInstance::Remove(const string space, 
		const string key, const T value) {
	mongo::BSONObjBuilder query;

	if ( key != "" ) {
		query.append(key, value); 
	}
	conn.remove(space, query.obj());

	string e = conn.getLastError();
	if ( !e.empty() ) {
		cout << "failed to remove : " << e << endl;
		exit(EXIT_FAILURE);
	}
}

void MongoInstance::Remove(const char * space) {
	mongo::BSONObjBuilder query;
	conn.remove(space, query.obj());
}

template <class T>
void MongoInstance::Insert(const string space, const string key, 
										const T value) {
	mongo::BSONObjBuilder query;
	query.append(key, value);
	conn.insert(space, query.obj());

	string e = conn.getLastError();
	if ( !e.empty() ) {
		cout << "failed to insert : " << e << endl;
		exit(EXIT_FAILURE);
	}
}

template <class T>
void MongoInstance::Update(const char * collname, const char * key, const T value, 
		    const char * ud_key, const T ud_value, bool isSet) {
	if ( isSet == false ) {
		BSONObj res = BSONObjBuilder().append(key, value).obj();	
		BSONObj after = BSONObjBuilder().appendElements(res).append(ud_key, ud_value).obj();
		conn.update(collname, res, after);
	}
	else {
		conn.update(collname, BSONObjBuilder().append(key, value).obj(), BSON("$set" << BSON(ud_key << ud_value)));
	}
}

void MongoInstance::Update(const char * collectName, BSONObj & res, BSONObj & obj) {
	if ( collectName != NULL ) {
		conn.connect(string("localhost:") + "27017");

		BSONObj after = BSONObjBuilder().appendElements(res).appendElements(obj).obj();
		conn.update(collectName, res, after);
	}
}

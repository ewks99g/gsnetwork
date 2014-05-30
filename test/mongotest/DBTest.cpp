/*******************************************************************
 *	Copyright(c) 2000-2013 linghegu
 *	All rights reserved.
 *	Author:	pengpeng
 *	CreatTime: 2014/05/30
 ******************************************************************/
#include "dbconnection.h"

/*#include "dbconnection.h"
 * */

using namespace mongo;
using namespace bson;
using namespace std;

class DBTest {
private:
	DBConnection conn;
	const char * testcoll;

public:
	/*
	 *mongo C++ interface Test function
	 *
	 *create DBClientConnection object, defalut connection: 127.0.0.1:27017
	 * */
	DBTest(bool autoreconn = false, int writemeoutsec = 3) : conn(autoreconn, writemeoutsec), testcoll("test.foo") {
		conn.connect("localhost:27017");
	}

	~DBTest() {}
	
	/*
	 *create an new Collection
	 * */
	void createAnCollection(const char * name) {
		conn.createCollection(name);
	}

	/*
	 *drop an Colletion
	 * */
	void dropAnCollection(const char * name) {
		conn.dropCollection(name);
	}

	/*
	 *execute a shell commend
	 * */
	void excuteAnCmd() {
		conn.excuteCmd("test", "count");
	}

	/*
	 *coll: insert object, it should be used as std::vector<mongo::BSONObj> 
	 *testcoll: insert collection
	 * */
	void insert_Test() {
		std::vector<mongo::BSONObj> coll;
		conn.remove(testcoll, BSONObj());

		{
			BSONObj * p = new BSONObj[3];
			p[0] = BSON("_id" << 1 << "foo" << BSON_ARRAY("bar" << "baz" << "qux"));
			p[1] = BSON("_id" << 2 << "name" << "joe" << "age" << 25);
			p[2] = BSON("_id" << 3 << "company" << "linghegu" << "city" << "beijing");
			for ( int i = 0; i < 3; ++i) {
				coll.push_back(p[i]);
			}
		}

		conn.insert(testcoll, coll);
	}

	/*
	 *remove(const char *, BSONObj()):	clear the collection
	 *remove(const char *, BSONObj(some query)):	clear data corrperate to query
	 *
	 * */
	void remove_Test() {
		
		{
			insert_Test();
			cout << "remove_test1 inititalize: " << endl;
			conn.printAll(testcoll);
			cout << "after remove All: " << endl;
			usleep(2000000);
			conn.remove(testcoll, BSONObj());
			conn.printAll(testcoll);
			cout << endl;
			usleep(2000000);
		}

		{
			insert_Test();
			cout << "remove_test2 initialize: " << endl;
			conn.printAll(testcoll);
			cout << "after remove _id of One: " << endl;
			usleep(2000000);
			conn.remove(testcoll, BSON("_id" << 1));
			conn.printAll(testcoll);
		}
	}
	
	/*
	 *testcoll:	collection
	 *testOne: find all of document include age "1" from collection
	 *testTwo: find only One document include age "1"
	 *
	 * */
	void find_Test() {
		std::vector<mongo::BSONObj> coll;
		conn.remove(testcoll, BSONObj());

		{
			BSONObj * p = new BSONObj[5];
			p[0] = (testcoll, BSON("name" << "joe" << "age" << 1));
			p[1] = (testcoll, BSON("name" << "joe" << "age" << 2));
			p[2] = (testcoll, BSON("name" << "joe" << "age" << 1));
			p[3] = (testcoll, BSON("name" << "joe" << "age" << 3));
			p[4] = (testcoll, BSON("name" << "joe" << "age" << 2));
			
			for ( int i = 0; i < 5; ++i) {
				coll.push_back(p[i]);
			}
			
			conn.insert(testcoll, coll);
			cout << "collection initialize: " << endl;
			conn.printAll(testcoll);
		}

		{
			usleep(1000000);
			cout << endl << "find age of 1(All): " << endl;
			usleep(2000000);
			BSONObj condition = BSONObjBuilder().append("age", 1).obj();
			std::vector<mongo::BSONObj> ret;
			
			conn.find(testcoll, condition, ret, 5);
			std::vector<mongo::BSONObj>::const_iterator pos;
			for ( pos = ret.begin(); pos != ret.end(); ++pos) {
				cout << (*pos).toString() << endl;
			}
		}

		{
			usleep(1000000);
			cout << endl << "find age of 1(One): " << endl;
			usleep(2000000);
			BSONObj condition = BSONObjBuilder().append("age", 1).obj();

			std::vector<mongo::BSONObj> ret;

			conn.find(testcoll, condition, ret, 1);
			std::vector<mongo::BSONObj>::const_iterator pos;
			for ( pos = ret.begin(); pos != ret.end(); ++pos) {
				cout << (*pos).toString() << endl;
			}
		}
	}

	/*
	 *testcoll:	update collection
	 *condition: which document to update, rely on this condition
	 *bo: update mathod
	 *
	 * */
	void update_Test() {
		std::vector<BSONObj> coll;
		conn.remove(testcoll, BSONObj());
	
		{
			BSONObj * p = new BSONObj[5];
			p[0] = (testcoll, BSON("name" << "linghegu" << "age" << 100));
			p[1] = (testcoll, BSON("name" << "wangbin" << "age" << 25));
			p[2] = (testcoll, BSON("name" << "jihuifeng" << "age" << 26));
			p[3] = (testcoll, BSON("name" << "zhengjingwei" << "age" << 21));
			p[4] = (testcoll, BSON("name" << "pengpeng" << "age" << 22));
			
			for ( int i = 0; i < 5; ++i) {
				coll.push_back(p[i]);
			}
			
			conn.insert(testcoll, coll);
			cout << endl << "collection initialize: " << endl;
			conn.printAll(testcoll);
		}

		{
			usleep(1000000);
			cout << "append gift (age > 24): " << endl;
			usleep(2000000);

			BSONObj condition = BSON("age" << BSON("$gt" << 24));
			bo op = BSON("$set" << BSON("gift" << "nice day!"));
			conn.update(testcoll, condition, op);

			conn.printAll(testcoll);
		}

		{
			usleep(1000000);
			cout << "adding an age for each: " << endl;
			usleep(2000000);

			BSONObj condition;
			bo op = BSON("$inc" << BSON("age" << 1));
			conn.update(testcoll, condition, op);

			conn.printAll(testcoll);
		}
	}
};


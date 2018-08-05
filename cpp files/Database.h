#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace sql;

#define DB_HOST "tcp://127.0.0.1/"
#define DB_PASS "barca60948"
#define DB_PORT 3306
#define DB_USER "d10s"
#define DB_NAME "the_bookshop"

#define CON Database &db = Database::getInstance();Connection *con = db.getConnection()

class Database {
private:
	// singleton instance
	static Database *instance;

	Driver *driver;
	ConnectOptionsMap connection_properties;

	// private CTOR (singleton)
	Database();
public:
	static Database& getInstance();

	Connection *getConnection();

	virtual ~Database() {}
};

#endif // !DATABASE_H

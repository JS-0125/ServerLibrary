#pragma once
#include<iostream>
#include<WinSock2.h>
#include <my_global.h>
#include <mysql.h>
#include<string>
#include<format>

#pragma comment(lib, "libmySQL.lib")

using namespace std;

class MySQLDataBase {
private:
	MYSQL mysql;
public:
	MySQLDataBase() {
		mysql_init(&mysql);
		if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "rkddkwltjs125@", "world", 3306, NULL, 0))
			cout << "error" << endl;
		else
			cout << "success"<<endl;
	}

	~MySQLDataBase() { mysql_close(&mysql);}

	bool DBLogin(const char* id) {
		string call = format("CALL Login{0}", id);

		int ret = mysql_query(&mysql, call.c_str());

	}
};

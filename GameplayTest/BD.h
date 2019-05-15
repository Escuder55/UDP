#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

class BD
{
public:

	//ATTRIBUTES
	sql::SQLString  Host;
	sql::SQLString  Username;
	sql::SQLString  Password;
	sql::SQLString  DataBase;

	sql::Driver* driver;
	sql::Connection* conn;

	sql::Statement* stmt;
	sql::ResultSet* res;

	//METODOS
	BD(sql::SQLString PHost, sql::SQLString PUsername, sql::SQLString PPassword, sql::SQLString PDataBase);
	void CheckUser();
	~BD();
};


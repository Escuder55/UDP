#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

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

	sql::PreparedStatement *prep_stmt = nullptr;
	sql::Statement* stmt = nullptr;
	sql::ResultSet* res = nullptr;

	//METODOS
	BD(sql::SQLString PHost, sql::SQLString PUsername, sql::SQLString PPassword, sql::SQLString PDataBase);
	bool CheckUser(sql::SQLString UserToSearch);
	void InsertNewUser(sql::SQLString user, sql::SQLString password, int Skin);
	bool LoginUser(sql::SQLString user, sql::SQLString password);
	~BD();
};

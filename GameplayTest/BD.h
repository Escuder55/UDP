#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include "Constants.h"
#include <vector>


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
	void InitBaseDatos();
	bool CheckUser(sql::SQLString UserToSearch);
	void InsertNewUser(sql::SQLString user, sql::SQLString password, int Skin);
	bool LoginUser(sql::SQLString user, sql::SQLString password);
	int TakeSkin(sql::SQLString user, sql::SQLString password);
	int getMonstersKilledPlayer(sql::SQLString PUsername, sql::SQLString PPassword);
	int getIdCuenta(sql::SQLString PUsername, sql::SQLString PPassword);
	void InicioSesion(int cuenta);
	int getSesionOfId(int cuenta);
	void InicioPartida(int sesion);
	int getPartidaActual(int sesion);
	//MAPA
	MapaGame getMap1();
	MapaGame getMap2();
	MapaGame getMap3();

	//MONSTERS
	std::vector<Enemy> getMonsterMap1();
	std::vector<Enemy> getMonsterMap2();
	std::vector<Enemy> getMonsterMap3();


	//DESTRUCTOR
	~BD();
};


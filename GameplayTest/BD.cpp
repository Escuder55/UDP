#include "BD.h"

BD::BD(sql::SQLString PHost, sql::SQLString PUsername, sql::SQLString PPassword, sql::SQLString PDataBase)
{
	Host = PHost;
	Username = PUsername;
	Password = PPassword;
	DataBase = PDataBase;

	try
	{
		driver = sql::mysql::get_driver_instance();
		conn = driver->connect(Host, Username, Password);
		conn->setSchema(DataBase);

		//CONEXION ESTABLECIDA
		std::cout << "Conexion con exito a la base de datos" << std::endl;

	}
	catch (sql::SQLException& e)
	{
		std::cout << "No se ha podido conectar" << std::endl;
	}
}

void BD::CheckUser()
{
}


BD::~BD()
{
	conn->close();
	delete res;
	delete stmt;
	delete conn;
}

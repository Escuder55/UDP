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

bool BD::CheckUser(sql::SQLString UserToSearch)
{
	prep_stmt = conn->prepareStatement("SELECT * from cuenta WHERE nick = ?");
	prep_stmt->setString(1, UserToSearch);
	res = prep_stmt->executeQuery();

	//COMPROBAMOS SI EXISTE EL USUARIO
	int cuantos = res->rowsCount();;
	if (cuantos > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

	delete res;
	delete prep_stmt;
}

void BD::InsertNewUser(sql::SQLString user, sql::SQLString password, int Skin)
{
	prep_stmt = conn->prepareStatement("INSERT INTO cuenta(nick, password, skin) values(?, ?, ?)");
	prep_stmt->setString(1, user);
	prep_stmt->setString(2, password);
	prep_stmt->setInt(3, Skin);
	res = prep_stmt->executeQuery();

	delete res;
	delete prep_stmt;
}

bool BD::LoginUser(sql::SQLString user, sql::SQLString password)
{
	prep_stmt = conn->prepareStatement("SELECT * from cuenta WHERE nick = ? && password = ?");
	prep_stmt->setString(1, user);
	prep_stmt->setString(2, password);
	res = prep_stmt->executeQuery();

	//COMPROBAMOS SI EXISTE EL USUARIO
	int cuantos = res->rowsCount();;
	if (cuantos > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

	delete res;
	delete prep_stmt;
}

int BD::TakeSkin(sql::SQLString user, sql::SQLString password)
{
	prep_stmt = conn->prepareStatement("SELECT skin from cuenta WHERE nick = ? && password = ?");
	prep_stmt->setString(1, user);
	prep_stmt->setString(2, password);
	res = prep_stmt->executeQuery();
	
	while (res->next())
	{
		return res->getInt("skin");
	}


	delete res;
	delete prep_stmt;

}





BD::~BD()
{
	conn->close();
	delete conn;
}

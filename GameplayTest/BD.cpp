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

MapaGame BD::getMap1()
{
	MapaGame map1;
	Sala sala1;
	Sala sala2;
	Sala sala3;
	Sala sala4;

	//SETEAMOS IDS
	map1.id_map = 1;
	sala1.id_sala = 1;
	sala2.id_sala = 2;
	sala3.id_sala = 3;
	sala4.id_sala = 4;

	//PUERTAS SALA1
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 1);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala1.puertas[0] = res->getInt("puerta1");
		sala1.puertas[1] = res->getInt("puerta2");
		sala1.puertas[2] = res->getInt("puerta3");
		sala1.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala1 puertas: " << sala1.puertas[0] << " " << sala1.puertas[1] << " " << sala1.puertas[2] << " " << sala1.puertas[3] << std::endl;

	//PUERTAS SALA2
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 2);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala2.puertas[0] = res->getInt("puerta1");
		sala2.puertas[1] = res->getInt("puerta2");
		sala2.puertas[2] = res->getInt("puerta3");
		sala2.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala2 puertas: " << sala2.puertas[0] << " " << sala2.puertas[1] << " " << sala2.puertas[2] << " " << sala2.puertas[3] << std::endl;

	//PUERTAS SALA3
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 3);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala3.puertas[0] = res->getInt("puerta1");
		sala3.puertas[1] = res->getInt("puerta2");
		sala3.puertas[2] = res->getInt("puerta3");
		sala3.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala3 puertas: " << sala3.puertas[0] << " " << sala3.puertas[1] << " " << sala3.puertas[2] << " " << sala3.puertas[3] << std::endl;

	//PUERTAS SALA4
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 4);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala4.puertas[0] = res->getInt("puerta1");
		sala4.puertas[1] = res->getInt("puerta2");
		sala4.puertas[2] = res->getInt("puerta3");
		sala4.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala4 puertas: " << sala4.puertas[0] << " " << sala4.puertas[1] << " " << sala4.puertas[2] << " " << sala4.puertas[3] << std::endl;

	//SETEAMOS MAP
	map1.salas[0] = sala1;
	map1.salas[1] = sala2;
	map1.salas[2] = sala3;
	map1.salas[3] = sala4;

	return map1;
}

MapaGame BD::getMap2()
{
	MapaGame map1;
	Sala sala1;
	Sala sala2;
	Sala sala3;
	Sala sala4;

	//SETEAMOS IDS
	map1.id_map = 1;
	sala1.id_sala = 5;
	sala2.id_sala = 6;
	sala3.id_sala = 7;
	sala4.id_sala = 8;

	//PUERTAS SALA1
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 5);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala1.puertas[0] = res->getInt("puerta1");
		sala1.puertas[1] = res->getInt("puerta2");
		sala1.puertas[2] = res->getInt("puerta3");
		sala1.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala1 puertas: " << sala1.puertas[0] << " " << sala1.puertas[1] << " " << sala1.puertas[2] << " " << sala1.puertas[3] << std::endl;

	//PUERTAS SALA2
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 6);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala2.puertas[0] = res->getInt("puerta1");
		sala2.puertas[1] = res->getInt("puerta2");
		sala2.puertas[2] = res->getInt("puerta3");
		sala2.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala2 puertas: " << sala2.puertas[0] << " " << sala2.puertas[1] << " " << sala2.puertas[2] << " " << sala2.puertas[3] << std::endl;

	//PUERTAS SALA3
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 7);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala3.puertas[0] = res->getInt("puerta1");
		sala3.puertas[1] = res->getInt("puerta2");
		sala3.puertas[2] = res->getInt("puerta3");
		sala3.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala3 puertas: " << sala3.puertas[0] << " " << sala3.puertas[1] << " " << sala3.puertas[2] << " " << sala3.puertas[3] << std::endl;

	//PUERTAS SALA4
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 8);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala4.puertas[0] = res->getInt("puerta1");
		sala4.puertas[1] = res->getInt("puerta2");
		sala4.puertas[2] = res->getInt("puerta3");
		sala4.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala4 puertas: " << sala4.puertas[0] << " " << sala4.puertas[1] << " " << sala4.puertas[2] << " " << sala4.puertas[3] << std::endl;

	//SETEAMOS MAP
	map1.salas[0] = sala1;
	map1.salas[1] = sala2;
	map1.salas[2] = sala3;
	map1.salas[3] = sala4;

	return map1;
}

MapaGame BD::getMap3()
{
	MapaGame map1;
	Sala sala1;
	Sala sala2;
	Sala sala3;
	Sala sala4;

	//SETEAMOS IDS
	map1.id_map = 1;
	sala1.id_sala = 9;
	sala2.id_sala = 10;
	sala3.id_sala = 11;
	sala4.id_sala = 12;

	//PUERTAS SALA1
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 9);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala1.puertas[0] = res->getInt("puerta1");
		sala1.puertas[1] = res->getInt("puerta2");
		sala1.puertas[2] = res->getInt("puerta3");
		sala1.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala1 puertas: " << sala1.puertas[0] << " " << sala1.puertas[1] << " " << sala1.puertas[2] << " " << sala1.puertas[3] << std::endl;

	//PUERTAS SALA2
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 10);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala2.puertas[0] = res->getInt("puerta1");
		sala2.puertas[1] = res->getInt("puerta2");
		sala2.puertas[2] = res->getInt("puerta3");
		sala2.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala2 puertas: " << sala2.puertas[0] << " " << sala2.puertas[1] << " " << sala2.puertas[2] << " " << sala2.puertas[3] << std::endl;

	//PUERTAS SALA3
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 11);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala3.puertas[0] = res->getInt("puerta1");
		sala3.puertas[1] = res->getInt("puerta2");
		sala3.puertas[2] = res->getInt("puerta3");
		sala3.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala3 puertas: " << sala3.puertas[0] << " " << sala3.puertas[1] << " " << sala3.puertas[2] << " " << sala3.puertas[3] << std::endl;

	//PUERTAS SALA4
	prep_stmt = conn->prepareStatement("SELECT puerta1, puerta2, puerta3, puerta4 FROM sala WHERE id_sala = ?");
	prep_stmt->setInt(1, 12);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		sala4.puertas[0] = res->getInt("puerta1");
		sala4.puertas[1] = res->getInt("puerta2");
		sala4.puertas[2] = res->getInt("puerta3");
		sala4.puertas[3] = res->getInt("puerta4");
	}

	//std::cout << "Sala4 puertas: " << sala4.puertas[0] << " " << sala4.puertas[1] << " " << sala4.puertas[2] << " " << sala4.puertas[3] << std::endl;

	//SETEAMOS MAP
	map1.salas[0] = sala1;
	map1.salas[1] = sala2;
	map1.salas[2] = sala3;
	map1.salas[3] = sala4;

	return map1;
}

BD::~BD()
{
	conn->close();
	delete conn;
}

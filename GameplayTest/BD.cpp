#include "BD.h"

BD::BD(sql::SQLString PHost, sql::SQLString PUsername, sql::SQLString PPassword, sql::SQLString PDataBase)
{
	Host = PHost;
	Username = PUsername;
	Password = PPassword;
	DataBase = PDataBase;
}

void BD::InitBaseDatos()
{	

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
	sala1.id_sala = 1;
	sala2.id_sala = 2;
	sala3.id_sala = 3;
	sala4.id_sala = 4;

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

	sala1.puertas[0] -= 4;
	sala1.puertas[1] -= 4;
	sala1.puertas[2] -= 4;
	sala1.puertas[3] -= 4;

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

	sala2.puertas[0] -= 4;
	sala2.puertas[1] -= 4;
	sala2.puertas[2] -= 4;
	sala2.puertas[3] -= 4;

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

	sala3.puertas[0] -= 4;
	sala3.puertas[1] -= 4;
	sala3.puertas[2] -= 4;
	sala3.puertas[3] -= 4;

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

	sala4.puertas[0] -= 4;
	sala4.puertas[1] -= 4;
	sala4.puertas[2] -= 4;
	sala4.puertas[3] -= 4;

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
	sala1.id_sala = 1;
	sala2.id_sala = 2;
	sala3.id_sala = 3;
	sala4.id_sala = 4;

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

	sala1.puertas[0] -= 8;
	sala1.puertas[1] -= 8;
	sala1.puertas[2] -= 8;
	sala1.puertas[3] -= 8;

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

	sala2.puertas[0] -= 8;
	sala2.puertas[1] -= 8;
	sala2.puertas[2] -= 8;
	sala2.puertas[3] -= 8;

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

	sala3.puertas[0] -= 8;
	sala3.puertas[1] -= 8;
	sala3.puertas[2] -= 8;
	sala3.puertas[3] -= 8;

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

	sala4.puertas[0] -= 8;
	sala4.puertas[1] -= 8;
	sala4.puertas[2] -= 8;
	sala4.puertas[3] -= 8;

	//std::cout << "Sala4 puertas: " << sala4.puertas[0] << " " << sala4.puertas[1] << " " << sala4.puertas[2] << " " << sala4.puertas[3] << std::endl;

	//SETEAMOS MAP
	map1.salas[0] = sala1;
	map1.salas[1] = sala2;
	map1.salas[2] = sala3;
	map1.salas[3] = sala4;

	return map1;
}

std::vector<Enemy> BD::getMonsterMap1()
{
	//VECTOR DE ENEMIGOS
	std::vector<Enemy> vecEnemies;

	//ENEMIGOS SALA 1
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 1);
	res = prep_stmt->executeQuery();

	//ENEMIGO AUXILIAR
	Enemy auxEnemy;

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 1;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 2
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 2);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 2;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 3
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 3);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 3;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 4
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 4);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 4;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	return vecEnemies;
}

std::vector<Enemy> BD::getMonsterMap2()
{
	//VECTOR DE ENEMIGOS
	std::vector<Enemy> vecEnemies;

	//ENEMIGOS SALA 1
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 5);
	res = prep_stmt->executeQuery();

	//ENEMIGO AUXILIAR
	Enemy auxEnemy;

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 1;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 2
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 6);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 2;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 3
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 7);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 3;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 4
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 8);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 4;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	return vecEnemies;
}

std::vector<Enemy> BD::getMonsterMap3()
{
	//VECTOR DE ENEMIGOS
	std::vector<Enemy> vecEnemies;

	//ENEMIGOS SALA 1
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 9);
	res = prep_stmt->executeQuery();

	//ENEMIGO AUXILIAR
	Enemy auxEnemy;

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 1;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 2
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 10);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 2;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 3
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 11);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 3;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	//ENEMIGOS SALA 4
	prep_stmt = conn->prepareStatement("SELECT id_monstruo, posicion_X, posicion_Y FROM monstruo WHERE sala = ?");
	prep_stmt->setInt(1, 12);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		auxEnemy.ID = res->getInt("id_monstruo");
		auxEnemy.ID_Sala = 4;
		auxEnemy.posX = res->getInt("posicion_X");
		auxEnemy.posY = res->getInt("posicion_Y");

		//PUSHEAMOS AL VECTOR
		vecEnemies.push_back(auxEnemy);
	}

	return vecEnemies;
}

int BD::getMonstersKilledPlayer(sql::SQLString PUsername, sql::SQLString PPassword)
{
	int enemiesKilled = 0;
	std::vector<int> Sesiones;
	int id_cuenta;
	int i;

	prep_stmt = conn->prepareStatement("SELECT id_cuenta from cuenta WHERE nick = ? && password = ?");
	prep_stmt->setString(1, PUsername);
	prep_stmt->setString(2, PPassword);
	res = prep_stmt->executeQuery();

	//COGEMOS EL ID DEL USUARIO
	res = prep_stmt->executeQuery();
	while (res->next())
	{
		id_cuenta = res->getInt("id_cuenta");
	}

	//TODAS LAS SESIONES QUE TENGA
	prep_stmt = conn->prepareStatement("SELECT id_sesion from sesiones WHERE cuenta = ?");
	prep_stmt->setInt(1, id_cuenta);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		Sesiones.push_back(res->getInt("id_sesion"));
	}

	//TODOS LOS MONSTRUOS MATADOS DE LA PARTIDA
	for (int i = 0; i < Sesiones.size(); i++)
	{
		prep_stmt = conn->prepareStatement("SELECT monstruos_matados from partida WHERE sesion = ?");
		prep_stmt->setInt(1, Sesiones[i]);
		res = prep_stmt->executeQuery();

		while (res->next())
		{
			enemiesKilled += res->getInt("monstruos_matados");
		}
	}

	delete res;
	delete prep_stmt;

	return enemiesKilled;
}

int BD::getIdCuenta(sql::SQLString PUsername, sql::SQLString PPassword)
{
	prep_stmt = conn->prepareStatement("SELECT id_cuenta from cuenta WHERE nick = ? && password = ?");
	prep_stmt->setString(1, PUsername);
	prep_stmt->setString(2, PPassword);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		return res->getInt("id_cuenta");
	}


	delete res;
	delete prep_stmt;

}

void BD::InicioSesion(int cuenta)
{
	prep_stmt = conn->prepareStatement("INSERT INTO sesiones(cuenta) VALUES(?)");
	prep_stmt->setInt(1, cuenta);
	res = prep_stmt->executeQuery();

	delete res;
	delete prep_stmt;
}

int BD::getSesionOfId(int cuenta)
{
	prep_stmt = conn->prepareStatement("SELECT id_sesion from sesiones WHERE cuenta = ? ORDER BY tiempoInicial DESC LIMIT 1");
	prep_stmt->setInt(1, cuenta);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		return res->getInt("id_sesion");
	}

	delete res;
	delete prep_stmt;
}

void BD::InicioPartida(int sesion)
{
	prep_stmt = conn->prepareStatement("INSERT INTO partida(monstruos_matados, sesion) VALUES(0, ?)");
	prep_stmt->setInt(1, sesion);
	res = prep_stmt->executeQuery();

	delete res;
	delete prep_stmt;
}

int BD::getPartidaActual(int sesion)
{
	prep_stmt = conn->prepareStatement("SELECT id_partida from partida WHERE sesion = ? ORDER BY inicio DESC LIMIT 1");
	prep_stmt->setInt(1, sesion);
	res = prep_stmt->executeQuery();

	while (res->next())
	{
		return res->getInt("id_partida");
	}

	delete res;
	delete prep_stmt;

	return 0;
}

void BD::UpdatePartida(int idPartida)
{
	prep_stmt = conn->prepareStatement("UPDATE partida SET final = CURRENT_TIMESTAMP() WHERE id_partida = ?");
	prep_stmt->setInt(1, idPartida);
	res = prep_stmt->executeQuery();

}

BD::~BD()
{
	conn->close();
	delete conn;
}

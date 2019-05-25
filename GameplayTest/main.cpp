#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <stack>
#include <thread>
#include <list>
#include <cstring>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include "Constants.h"
#include "Game.h"
#include "FirstChoice.h"
#include "LogIn.h"
#include "Menu.h"
#include "SignUp.h"
#include "Maps.h"
#include "Mensaje.h"
#include "PlayerProxy.h"
#include "BD.h"
#include "BinaryTree.h"
#include <map>

//PACKET SOBRECARGADO
sf::Packet& operator <<(sf::Packet& packet, const PROTOCOLO& orders)
{
	int option = static_cast<int>(orders);
	return packet << option;
}
sf::Packet& operator >>(sf::Packet& packet, PROTOCOLO& orders)
{
	int option = static_cast<int>(orders);
	return packet >> option;
}

TypeScene sceneState;
/////////////////////////////////////////// VARIABLES COMPARTIDAS
PROTOCOLO orders;

//////////////////////////////////////////	VARIABLES PARA EL CLIENTE
sf::Socket::Status status;
sf::Packet pack;
sf::UdpSocket socket;
PlayerProxy proxy;

//////////////////////////////////////////	VARIABLES PARA EL SERVER
//// CURRENTTIMESTAMP para fecha
//PLAYER PROXIES
std::vector<PlayerProxy> playersConnecteds;

/////////////////////////////////////////////////////////Variables sin categoria

Game *myGameScene;

////////////////////////////////////////funcio para encontrar la id del usuario que envia el mensaje
int getId(sf::IpAddress _adres, unsigned short _port)
{
	int ID = 0;


	for (int i = 0; i < playersConnecteds.size(); i++)
	{
		if (playersConnecteds[i].IP_Adress == _adres && playersConnecteds[i].port == _port)
		{
			ID = i;
		}
	}
	return ID;
}
//MENSAJES CRITICOS
//std::list<std::stack<Mensaje>> paquetes_criticos;
std::multimap<int, Mensaje> paquetes_criticos;

//MENSAJES NORMALES

//std::list<std::stack<Mensaje>> paquetes_normales;

//LOGIN/REGISTER
bool YouCanLogin;
bool YouCanSignUp;
int auxId;
int auxIdPacket;

//MAPA Y SALAS
struct Salas
{
	int id_sala;
	int puertas[4];
};

struct Map
{
	int id_map;
	Salas salas[4];
};

//TIMER
clock_t startTime;
clock_t endTime;
clock_t clockTicksTaken;
double timeInSeconds;

bool helloMessage = false;
////////puntero a la escena actual
Scene* currentScene;


///////Struct para el game

struct gameProxy
{
	int id;
	int idMAp;
	std::vector<PlayerProxy> players;
	std::vector<Enemy> EnemiesGame;
	bool full = false;
};
struct waitingPlayer
{
	int id;
	int map;
	int numEnemies;
};

std::vector<gameProxy> gamesProxy;
std::vector<waitingPlayer> playersWaitingMap1;
std::vector<waitingPlayer> playersWaitingMap2;
std::vector<waitingPlayer> playersWaitingMap3;

//aux
std::vector<PlayerProxy> auxPlayers;
std::vector<Enemy> auxEnemy;


std::multimap<int, Mensaje> listOfCritics;

int games = 0;
gameProxy auxGame;
///////////////////////////////////////// CLIENTE PARTIDA

gameProxy myGame;

/////////////////////MUTEX
std::mutex mutex;

/////////////////////////////////////////////////////////////////////////////------------------------VARIABLES SERVER
int numPlayers = 0;
//// ------------------------ MENSAJE RECIBIDO ----------------- ////
PlayerProxy auxPlayerProxy;
sf::IpAddress adress;
unsigned short port;

//// ------------- BASE DE DATOS ------------------ //
BD* BaseDatos;
sql::SQLString HOSTBD = "tcp://www.db4free.net:3306";
sql::SQLString USERNAMEBD = "puajklejos";
sql::SQLString PASSWORDBD = "Puajklejos95*";
sql::SQLString DATABASEBD = "practicaredes";

// VARIABLES BASE DE DATOS
sql::SQLString SQLusername;
sql::SQLString SQLpassword;
std::string skin;
int SQLSkin;
//// ------------------------- SET MAPS --------------------- ////
MapaGame map1;
MapaGame map2;
MapaGame map3;


///////////--------------- COMPROBAR SI YA ESTA ESPERANDO PARTIDA --------------- ////////////
bool IsInTheList(int id) 
{
	if (!playersWaitingMap1.empty())
	{
		for (int i = 0; i < playersWaitingMap1.size(); i++)
		{
			if (playersWaitingMap1[i].id == id)
			{
				return  true;
			}
		}
	}	
	if (!playersWaitingMap2.empty())
	{
		for (int i = 0; i < playersWaitingMap2.size(); i++)
		{
			if (playersWaitingMap2[i].id == id)
			{
				return  true;
			}
		}
	}
	if (!playersWaitingMap3.empty())
	{
		for (int i = 0; i < playersWaitingMap3.size(); i++)
		{
			if (playersWaitingMap3[i].id == id)
			{
				return  true;
			}
		}
	}
	return false;
}

//THREAD RECEIVE SERVER
void ServerReceive()
{
	
	//BD BaseDatos(HOSTBD, USERNAMEBD, PASSWORDBD, DATABASEBD);
	BaseDatos = new BD(HOSTBD, USERNAMEBD, PASSWORDBD, DATABASEBD);
	BaseDatos->InitBaseDatos();

	map1 = BaseDatos->getMap1();
	map2 = BaseDatos->getMap2();
	map3 = BaseDatos->getMap3();

	//// --------------------- BINARY TREES -------------------- ////
	BinaryTree BST;

	//// -------------------- MONSTERS SALA -------------------- ////
	map1.enemiesMap = BaseDatos->getMonsterMap1();
	map2.enemiesMap = BaseDatos->getMonsterMap2();
	map3.enemiesMap = BaseDatos->getMonsterMap3();

	/*for (int i = 0; i < map1.enemiesMap.size(); i++)
	{
		std::cout << "Enemigos: " << map1.enemiesMap[i].ID << " " << map1.enemiesMap[i].ID_Sala << " " << map1.enemiesMap[i].posX << " " << map1.enemiesMap[i].posY << std::endl;
	}*/

	
	int auxSala;

	std::cout << "ENTRO EN EL THREAD" << std::endl;

	while (true)
	{
		pack.clear();
		status = socket.receive(pack, adress, port);	

		if (status == sf::Socket::Done)
		{
			//VARIABLES A UTILIZAR
			std::string username;
			std::string password;
			std::string repeatPassword;

			//std::cout << "Adress: " << adress << std::endl;
			//std::cout << "Port: " << port << std::endl;
			//PROTOCOLO A DAR
			int auxOrder;			

			pack >> auxOrder;
			orders = static_cast<PROTOCOLO>(auxOrder);

			//COMPROBACION
			
			//std::cout << "He recibido lo siguiente: "  << auxOrder << std::endl;

			bool newPlayer = true;
			int currentId;

			switch (orders)
			{
			case PROTOCOLO::HELLO:
			{
				
				////// ---------- COMPROBAMOS SI ESTE NO ES EL PRIMER HELLO DE ESTE CLIENTE ---------- //////
				for (int i = 0; i < playersConnecteds.size(); i++)
				{
					if (playersConnecteds[i].IP_Adress == adress && playersConnecteds[i].port == port)
					{
						newPlayer = false;
						currentId = i;
					}
				}

				/////////////////si el usuario es nuevo
				if (newPlayer)
				{
					////// ---------- GUARDAMOS INFO DE CONEXION DEL PLAYER ---------- //////
					numPlayers++;
					auxPlayerProxy.IP_Adress = adress;
					auxPlayerProxy.port = port;
					auxPlayerProxy.id = numPlayers;
					playersConnecteds.push_back(auxPlayerProxy);
					mutex.lock();
					playersConnecteds[getId(adress, port)].Regular_Message.insert({ PROTOCOLO::HELLO, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack) });
					mutex.unlock();
					std::cout << " Se ha recibido un nuevo cliente." << std::endl;
				}
				else
				{
					playersConnecteds[getId(adress, port)].Regular_Message.insert({ PROTOCOLO::HELLO, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack) });
				}


				break;
			}
			case PROTOCOLO::REGISTER:
			{
				playersConnecteds[getId(adress, port)].Regular_Message.insert({ PROTOCOLO::REGISTER, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack) });
				break;
			}
			case PROTOCOLO::LOGIN:
			{				
				playersConnecteds[getId(adress, port)].Regular_Message.insert({PROTOCOLO::LOGIN, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack)});
				break;
			}
			case PROTOCOLO::WANTPLAY:
			{
				playersConnecteds[getId(adress, port)].Regular_Message.insert({ PROTOCOLO::WANTPLAY, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack) });
				pack >> auxSala;
				switch (auxSala)
				{
				case 1:
				{
					if (!IsInTheList(playersConnecteds[getId(adress, port)].id))
					{
						playersWaitingMap1.push_back({ getId(adress, port)+1 ,1,playersConnecteds[getId(adress, port)].NumEnemigos });
						std::cout << "Quieren entrar!                     fewefew" << std::endl;
					}					
					break;
				}
				case 2:
				{
					if (!IsInTheList(getId(adress, port)))
					{
						playersWaitingMap2.push_back({ getId(adress, port) +1 ,2,playersConnecteds[getId(adress, port)].NumEnemigos });
					}

					break;
				}
				case 3:
				{
					if (!IsInTheList(getId(adress, port)))
					{
						playersWaitingMap3.push_back({ getId(adress, port) + 1 ,3,playersConnecteds[getId(adress, port)].NumEnemigos });
					}

					break;
				}
				default:
					std::cout << "No se ha recicbido bien la sala que se quiere jugar." << std::endl;
					break;
				}
				if (gamesProxy.size() == 0)
				{					
					//games++;
					//gamesProxy.push_back{games,});
				}
				break;
			}
			case PROTOCOLO::STARTGAMEACCEPTED:
			{	
				std::cout << "aqui 1" << std::endl;
				mutex.lock();
				if (playersConnecteds[getId(adress, port)].Critic_Message.count(PROTOCOLO::STARTGAME) > 0)
				{
					playersConnecteds[getId(adress, port)].Critic_Message.find(PROTOCOLO::STARTGAME)->second.id = -1;
				}
				mutex.unlock(); 
				break;
			}				
			case PROTOCOLO::MOVEMENT:
			{
				pack >> currentId;
				mutex.lock();
				playersConnecteds[getId(adress, port)].Regular_Message.insert({ PROTOCOLO::MOVEMENT, Mensaje(currentId, pack)});
				mutex.unlock();

				//std::cout << "ID aAcumulado : " << currentId;
				break;
			}
			default:
					break;
			}
		}
		else if(status != sf::Socket::Done)
		{
			//std::cout << "No he recibido nada" << std::endl;
		}
	}
	//std::cout << "fuga" << std::endl;
}

//THREAD PAQUETES NORMALES
void SendRegularPack()
{
	//////////// ------------ VARIABLES A UTILIZAR ------------ ////////////
	int iterador = 0 ;
	int aux = 0;
	bool newPlayer = true;
	int currentId;

	std::string username;
	std::string password;
	std::string repeatPassword;

	//KILLED MONSTERS
	int KilledMonsters;

	//MOVEMENT
	float posX[5];
	float posY[5];
	bool OKMovement = false;

	//std::cout << "Adress: " << adress << std::endl;
	//std::cout << "Port: " << port << std::endl;

	sf::Packet auxPacket;
	int packetidint;
	float auxPacketInt;

	//PROTOCOLO A DAR
	int auxOrder;
	PROTOCOLO auxProtocolo= PROTOCOLO::NONEPROTOCOLO;

	int tonteria = 0;
	//////// --------------- INICIALIZAR EL RELOJ QUE COMPRUEBA EL MATCHMAKING  --------------- ////////
	startTime = clock();


	while (true)
	{

		if (!playersConnecteds.empty())
		{
			tonteria = playersConnecteds[iterador].Regular_Message.size();
			if (tonteria > 0)
			{
				auxProtocolo = PROTOCOLO::NONEPROTOCOLO;
				aux = 0;
				//std::cout << " Jugador nº: " << iterador << std::endl;
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::HELLO))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::HELLO);
					auxProtocolo = PROTOCOLO::HELLO;
					//std::cout << "0" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::LOGIN))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::LOGIN);
					auxProtocolo = PROTOCOLO::LOGIN;
					std::cout << "1" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::REGISTER))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::REGISTER);
					auxProtocolo = PROTOCOLO::REGISTER;
					std::cout << "2" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::ROOMCHANGE))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::ROOMCHANGE);
					auxProtocolo = PROTOCOLO::ROOMCHANGE;
					std::cout << "3" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::DISCONECTED))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::DISCONECTED);
					auxProtocolo = PROTOCOLO::DISCONECTED;
					std::cout << "4" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::WANTPLAY))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::WANTPLAY);
					auxProtocolo = PROTOCOLO::WANTPLAY;
					std::cout << "5" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::MOVEMENT))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::MOVEMENT);
					auxProtocolo = PROTOCOLO::MOVEMENT;
					//std::cout << "6" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::TEAMPOSITION))
				{
					aux = playersConnecteds[iterador].Regular_Message.count(PROTOCOLO::TEAMPOSITION);
					auxProtocolo = PROTOCOLO::TEAMPOSITION;
					//std::cout << "6" << std::endl;
				}

				switch (auxProtocolo)
				{
					case HELLO:
					{
						/////// ----------- CONTESTAMOS AL MENSAJE HELLO ------------- ///////
						std::cout << "CONTESTANDO AL HELLO\n";
						auxPacket.clear();
						auxPacket << PROTOCOLO::WELCOME;
						auxPacket << playersConnecteds[iterador].id;
						socket.send(auxPacket, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);

						/////// ----------- BORRAMOS EL MENSAJE DE LA LISTA DE CRITICOS ------------- ///////
						mutex.lock();
						playersConnecteds[iterador].Regular_Message.erase(auxProtocolo);
						mutex.unlock();
						break;
					}
					case REGISTER:
					{
						std::cout << "CONTESTANDO AL SIGN UP\n";

						auxPacket = playersConnecteds[iterador].Regular_Message.find(auxProtocolo)->second.pack;

						auxPacket >> auxId;
						auxPacket >> auxIdPacket;
						auxPacket >> username;
						auxPacket >> password;
						auxPacket >> repeatPassword;
						auxPacket >> skin;

						YouCanSignUp = false;

						if(password == repeatPassword)
						{
							SQLusername = username.c_str();
							SQLpassword = password.c_str();
							SQLSkin = std::atoi(skin.c_str());

							//COMPROVACION
							std::cout << "Register with User:		" << username << std::endl;
							std::cout << "Register with Password:	" << password << std::endl;
							std::cout << "Register with Skin:	" << skin << std::endl;

							//CONSULTA 
							YouCanSignUp = !BaseDatos->CheckUser(SQLusername);
							std::cout << "El usuario puede registrarse? " << YouCanSignUp << std::endl;

							if (YouCanSignUp)
							{
								BaseDatos->InsertNewUser(SQLusername, SQLpassword, SQLSkin);

								for (int i = 0; i < playersConnecteds.size(); i++)
								{
									if (playersConnecteds[i].IP_Adress == adress)
									{
										playersConnecteds[i].userName = username;
										playersConnecteds[i].skin = SQLSkin;

										std::cout << "EL usuario con id: " << playersConnecteds[i].id
											<< " \nUser: " << playersConnecteds[i].userName
											<< " \nSkin: " << playersConnecteds[i].skin << std::endl;

									}
								}

								//COGEMOS MONSTRUOS MATADOS DEL USUARIO
								KilledMonsters = BaseDatos->getMonstersKilledPlayer(SQLusername, SQLpassword);
								playersConnecteds[iterador].id_cuenta = BaseDatos->getIdCuenta(SQLusername, SQLpassword);
								std::cout << "Enemigos matados: " << KilledMonsters << std::endl;
								playersConnecteds[iterador].NumEnemigos = KilledMonsters;
							}
						}


						//SEND TO CLIENT
						auxPacket.clear();
						auxPacket << PROTOCOLO::REGISTERACCEPTED << playersConnecteds[iterador].id << YouCanSignUp;
						socket.send(auxPacket, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);

						/////// ----------- BORRAMOS EL MENSAJE DE LA LISTA DE CRITICOS ------------- ///////
						playersConnecteds[iterador].Regular_Message.erase(auxProtocolo);
						break;
					}
					case LOGIN:
					{
						std::cout << "CONTESTANDO AL LOG IN\n";

						auxPacket = playersConnecteds[iterador].Regular_Message.find(auxProtocolo)->second.pack;

						auxPacket >> auxId;
						auxPacket >> auxIdPacket;
						auxPacket >> username;
						auxPacket >> password;

						SQLusername = username.c_str();
						SQLpassword = password.c_str();

						std::cout << "La ID_Cuenta es:  " << playersConnecteds[iterador].id_cuenta << std::endl;

						std::cout << "He recibido un intento de Login." << std::endl;
						//COMPROVACION
						for (int i = 0; i < playersConnecteds.size(); i++)
						{
							if (playersConnecteds[i].id == auxId)
							{
								std::cout	<< "El usuario con id: " << auxId
											<< "\nHa enviado el paquete con id: " << auxIdPacket
											<< "\nLog in User: " << username << std::endl;
								std::cout	<< "Log in Password:	" << password << std::endl;

								//CONSULTA 
								YouCanLogin = BaseDatos->LoginUser(SQLusername, SQLpassword);
								std::cout << "El usuario puede entrar? " << YouCanLogin << std::endl;

								if (YouCanLogin)
								{
									//COGEMOS MONSTRUOS MATADOS DEL USUARIO
									KilledMonsters = BaseDatos->getMonstersKilledPlayer(SQLusername, SQLpassword);
									playersConnecteds[iterador].id_cuenta = BaseDatos->getIdCuenta(SQLusername, SQLpassword);
									std::cout << "Enemigos matados: " << KilledMonsters << std::endl;
									playersConnecteds[iterador].NumEnemigos = KilledMonsters;
									playersConnecteds[i].skin = BaseDatos->TakeSkin(SQLusername, SQLpassword);
								}

								//SEND TO CLIENT
								auxPacket.clear();
								auxPacket << PROTOCOLO::LOGINACCEPTED << auxPlayerProxy.id << YouCanLogin << playersConnecteds[i].skin;
								socket.send(auxPacket, playersConnecteds[i].IP_Adress, playersConnecteds[i].port);
								
							}
							else
							{
								std::cout << "he recibido el intento de login pero no coincie con ningun usuario " << std::endl;
							}
						}					
							playersConnecteds[iterador].Regular_Message.erase(auxProtocolo);
						break;
					}
					case WANTPLAY:
					{
						std::cout << "CONTESTANDO A WANT PLAY\n";
						auxPacket.clear();
						auxPacket << PROTOCOLO::WANTPLAYACCEPTED;
						socket.send(auxPacket, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);

						/////// ----------- BORRAMOS EL MENSAJE DE LA LISTA DE CRITICOS ------------- ///////
						playersConnecteds[iterador].Regular_Message.erase(auxProtocolo);

						break;
					}
					case STARTGAME:
					{
						std::cout << "CONTESTANDO A WANTPLAY\n";
						break;
					}
					case ROOMCHANGE:
					{
						break;
					}
					case DISCONECTED:
					{
						break;
					}
					case MOVEMENT:
					{
						auxPacket = playersConnecteds[iterador].Regular_Message.find(auxProtocolo)->second.pack;
						for (int i = 0; i < 5; i++)
						{
							auxPacket >> posX[i];
							auxPacket >> posY[i];

							OKMovement = true;
							if (OKMovement)
							{

							}
						}
						if (OKMovement)
						{

							mutex.lock();
							//ACTUALIZO LA POSICION DEL JUGADOR QUE HA ENVIADO EL MOVIMIENTO
							playersConnecteds[iterador].posX = posX[4];
							playersConnecteds[iterador].posY = posY[4];
							mutex.unlock();

							auxPacket.clear();
							auxPacket << PROTOCOLO::MOVEMENT;
							auxPacket << playersConnecteds[iterador].Regular_Message.find(PROTOCOLO::MOVEMENT)->second.id;
							status = socket.send(auxPacket, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);
							if (status == sf::Socket::Done)
							{
								//ELIMINAMOS LOS PAQUETES ANTERIORES
								for (std::multimap<PROTOCOLO, Mensaje>::iterator it = playersConnecteds[iterador].Regular_Message.begin(); it != playersConnecteds[iterador].Regular_Message.end(); ++it)
								{
									if ((*it).first == PROTOCOLO::MOVEMENT)
									{
										if ((*it).second.id < playersConnecteds[iterador].Regular_Message.find(PROTOCOLO::MOVEMENT)->second.id)
										{
											playersConnecteds[iterador].Regular_Message.erase(it);
										}
									}
								}

								std::multimap<PROTOCOLO, Mensaje>::iterator it2 = playersConnecteds[iterador].Regular_Message.find(PROTOCOLO::MOVEMENT);
								playersConnecteds[iterador].Regular_Message.erase(it2);
								
								//Enviamos a todos los otros jugadores esta info////////////////////////////////////////////
								//Rellenamos paquete
								auxPacket.clear();
								auxPacket << PROTOCOLO::TEAMPOSITION;
								auxPacket << playersConnecteds[iterador].id;
								auxPacket << playersConnecteds[iterador].posX;
								auxPacket << playersConnecteds[iterador].posY;
								for (int i = 0; i < gamesProxy.size(); i++)
								{
									if (gamesProxy[i].id == playersConnecteds[iterador].idPartidaActual)
									{
										//Recorremos el vector de jugadores introduciendo el packet que deberemos enviar
										for (int j = 0; j < gamesProxy[i].players.size(); j++)
										{
											if (gamesProxy[i].players[j].id != playersConnecteds[iterador].id) 
											{
												playersConnecteds[gamesProxy[i].players[j].id-1].Regular_Message.insert({ PROTOCOLO::TEAMPOSITION, Mensaje(playersConnecteds[iterador].id,auxPacket) });
											}
										}
									}
								}
								//////////////////////////////////////////////////////////////////////////////////////////
							}
							else
							{
								std::cout << "No pude enviar el movimiento acumulado" << std::endl;
							}
						}
						break;
					}
					case TEAMPOSITION:
					{
						//std::cout << "----------------------------------------------" << std::endl;
						auxPacket = playersConnecteds[iterador].Regular_Message.find(PROTOCOLO::TEAMPOSITION)->second.pack;
						status = socket.send(auxPacket, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);
						if (status == sf::Socket::Done)
						{
							std::cout << "Enviado movimiento de un jugador a otro" << std::endl;
							std::multimap<PROTOCOLO, Mensaje>::iterator itToRemove = playersConnecteds[iterador].Regular_Message.find(PROTOCOLO::TEAMPOSITION);
							playersConnecteds[iterador].Regular_Message.erase(itToRemove);
						}
						else
						{
							std::cout << "No pude enviar el movimiento acumulado" << std::endl;
						}
						break; 
					}
					default:
					{
						std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
						break;
					}
				}

				iterador++;

				if (iterador > playersConnecteds.size()-1)
				{
					iterador = 0;
				}
				aux = 0;
			}
			else
			{
				iterador++;
				if (iterador > playersConnecteds.size()-1)
				{
					iterador = 0;
				}
			}
		}

		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;

		if (timeInSeconds >= 5)
		{
			startTime = clock();
			int playerForMap1 = 0;
			int playerForMap2 = 0;
			int playerForMap3 = 0;
			int idPlayers[4] = {-1,-1,-1,-1};
			//Ordenamos maps wantplay de cada mapa

			/////////// -------------- HACER EL MATCHMAKING MAPA1-------------- //////////////
			
				if (playersWaitingMap1.size() >= 2)
				{
					std::cout << "EMPIEZA LA PARTIDA" << std::endl;
					gamesProxy.push_back({games,1,auxPlayers,auxEnemy});
					games++;
					//rellenar Players
					for (int i=0;i<2;i++)
					{
						//rellenar Players
						for (int j = 0; j < playersConnecteds.size();j++)
						{
							if (playersWaitingMap1[i].id == playersConnecteds[j].id)
							{
								gamesProxy.back().players.push_back(playersConnecteds[j]);
								playersConnecteds[j].idPartidaActual = games - 1;
								//playersWaitingMap1.erase(playersWaitingMap1.begin());
								idPlayers[i] = j;
								std::cout << "UNA VEZ!!!!!!!!!!!!!!!!!!!!!!!!" <<j<< std::endl;
							}							
						}
						
					}

					for (int i = 0; i < 2; i++)
					{
						playersWaitingMap1.erase(playersWaitingMap1.begin());
					}

					for (int i=0;i<map1.enemiesMap.size();i++)
					{
						gamesProxy.back().EnemiesGame = map1.enemiesMap;
					}

					auxPacket.clear();
					auxPacket << PROTOCOLO::STARTGAME;
					auxPacket << playersConnecteds[idPlayers[0]].id << 200.f << 150.f;
					auxPacket << playersConnecteds[idPlayers[1]].id << 700.f << 150.f;
					//auxPacket << playersConnecteds[idPlayers[2]].id << 100 << 400;
					//auxPacket << playersConnecteds[idPlayers[3]].id << 700 << 400;

					//BUSCAR POR ID!
					for (int i = 0; i < 2; i++)
					{	
						for (int j = 0; j < playersConnecteds.size(); j++)
						{
							if (gamesProxy.back().players[i].id== playersConnecteds[j].id)
							{
								mutex.lock();
								playersConnecteds[j].Critic_Message.insert({ PROTOCOLO::STARTGAME,Mensaje(0,auxPacket) });
								mutex.unlock();
							}							
						}						
					}
					
				}
				if (playersWaitingMap2.size() >= 2)
				{
					//crear partida y push
					std::cout << "EMPIEZA LA PARTIDA" << std::endl;
					gamesProxy.push_back({ games,2,auxPlayers,auxEnemy });
					games++;
						//rellenar Players
					for (int i = 0; i < 4; i++)
					{
						//rellenar Players

					}
					for (int i = 0; i < map1.enemiesMap.size(); i++)
					{
						//gamesProxy.back().EnemiesGame.pushback(map1.enemiesMap[i]);
					}
				}
				if (playersWaitingMap3.size() >= 4)
				{
					//crear partida y push
					std::cout << "EMPIEZA LA PARTIDA" << std::endl;
					gamesProxy.push_back({ games,3,auxPlayers,auxEnemy });
					games++;
						//rellenar Players
					for (int i = 0; i < 4; i++)
					{
					

					}
					for (int i = 0; i < map1.enemiesMap.size(); i++)
					{
						//gamesProxy.back().EnemiesGame.pushback(map1.enemiesMap[i]);
					}
				}
		}

	}

}

//THREAD PAQUETES CRÍTICOS
void SendCriticPack()
{
	//////////// ------------ VARIABLES A UTILIZAR ------------ ////////////
	int iterador = 0;
	int aux = 0;
	bool newPlayer = true;
	int currentId;

	std::string username;
	std::string password;
	std::string repeatPassword;

	//KILLED MONSTERS
	int KilledMonsters;

	//std::cout << "Adress: " << adress << std::endl;
	//std::cout << "Port: " << port << std::endl;

	sf::Packet auxPacket;

	//PROTOCOLO A DAR
	int auxOrder;
	PROTOCOLO auxProtocolo = PROTOCOLO::NONEPROTOCOLO;

	//////// --------------- INICIALIZAR EL RELOJ QUE COMPRUEBA EL MATCHMAKING  --------------- ////////
	startTime = clock();
	int tonteriaCritic = 0;
	while (true)
	{
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		if (!playersConnecteds.empty())
		{
			tonteriaCritic = playersConnecteds[iterador].Critic_Message.size();
			if (tonteriaCritic > 0)
			{

				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::ROOMCHANGE))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::ROOMCHANGE);
					auxProtocolo = PROTOCOLO::ROOMCHANGE;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::DISCONECTED))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::DISCONECTED);
					auxProtocolo = PROTOCOLO::DISCONECTED;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::STARTGAME))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::STARTGAME);
					auxProtocolo = PROTOCOLO::STARTGAME;
				}

				switch (auxProtocolo)
				{
				case STARTGAME:
				{
					if (timeInSeconds > 2.5) 
					{
						startTime = clock();
						std::cout << "ENVIANDO EL CRITICO DE START GAME. \n";
						mutex.lock();
						if(playersConnecteds[iterador].Critic_Message.find(PROTOCOLO::STARTGAME)->second.id != -1)
						{
							socket.send(playersConnecteds[iterador].Critic_Message.find(PROTOCOLO::STARTGAME)->second.pack, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);
						}
						else
						{
							std::cout << "Borrando el StartGame del id: " << (getId(playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port) + 1) << std::endl;
							playersConnecteds[iterador].Critic_Message.erase(PROTOCOLO::STARTGAME);
						}
						mutex.unlock();
					}
					break;
				}
				case ROOMCHANGE:
				{
					std::cout << "ENVIANDO EL CRITICO DE ROOM CHANGE. \n";
					socket.send(playersConnecteds[iterador].Critic_Message.find(PROTOCOLO::STARTGAME)->second.pack, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);
					break;
				}
				case DISCONECTED:
				{
					std::cout << "ENVIANDO EL CRITICO DE DISCONECTED. \n";
					socket.send(playersConnecteds[iterador].Critic_Message.find(PROTOCOLO::STARTGAME)->second.pack, playersConnecteds[iterador].IP_Adress, playersConnecteds[iterador].port);
					break;
				}
				default:
				{
					//std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
					break;
				}
				}
				iterador++;
				if (iterador > playersConnecteds.size() - 1)
				{
					iterador = 0;
				}
				aux = 0;
			}
			else
			{
				iterador++;
				if (iterador > playersConnecteds.size() - 1)
				{
					iterador = 0;
				}
			}
		}
	}
}

//////////////////////////////////////////
////////////////////////////////////////// SERVER
//////////////////////////////////////////

void serverMain()
{	
	status = socket.bind(PORT);
	if (status != sf::Socket::Done)
	{
		std::cout << "no se puede hacer bind bien con el puerto" << PORT << std::endl;
	}
	else
	{
		std::cout << "Se hace bind bien con el puerto" << PORT << std::endl;
	}

	//THREAD RECEIVE
	std::thread threadServer(&ServerReceive);
	threadServer.detach();

	std::thread threadRegular(&SendRegularPack);
	threadRegular.detach();

	std::thread threadCritic(&SendCriticPack);
	threadCritic.detach();
	while (1)
	{

	}
}

float posX, posY;
//THREAD RECEIVE CLIENT
void ClientReceive()
{
	sf::IpAddress auxIP;
	unsigned short auxport;
	sf::Packet packRecieve;
	PlayerProxy teamMateAux;
	int auxint=-1;

	while (true)
	{

		//COMPROBACION
		packRecieve.clear();

		//mutex.lock();
		status = socket.receive(packRecieve, auxIP, auxport);
		//mutex.unlock();
		if (status != sf::Socket::Done)
		{
			//std::cout << "No se ha podido recibir el mensaje" << std::endl;
		}
		else
		{
			//std::cout << "Se ha recibido el mensaje" << std::endl;
			//RECOGEMOS VARIABLES
			int auxOrder;
			packRecieve >> auxOrder;

			orders = static_cast<PROTOCOLO>(auxOrder);

			switch (orders)
			{
			case PROTOCOLO::WELCOME:
				packRecieve >> proxy.id;
				helloMessage = true;
				std::cout << "El servidor te da la bienvenida con el siguiente id: " << proxy.id << std::endl;
				break;
			case PROTOCOLO::LOGINACCEPTED:

				packRecieve >> proxy.id;
				packRecieve >> YouCanLogin;
				std::cout << "Me puedo conectar: " << YouCanLogin << std::endl;
				if (YouCanLogin)
				{					
					packRecieve >> proxy.skin;
					currentScene->finishSending = true;
					sceneState = TypeScene::GOTO_MENU;
				}
				else
				{

					currentScene->finishSending = true;
					sceneState = TypeScene::GOTO_LOG_IN;
				}
				break;
			case PROTOCOLO::REGISTERACCEPTED:
				packRecieve >> proxy.id;
				packRecieve >> YouCanSignUp;
				std::cout << "Me puedo registrar: " << YouCanSignUp << std::endl;
				if (YouCanSignUp)
				{			
					currentScene->finishSending = true;
					sceneState = TypeScene::GOTO_MENU;
				}
				else
				{
					currentScene->finishSending = true;
					sceneState = TypeScene::GOTO_SIGN_UP;
				}

				break;
			case PROTOCOLO::WANTPLAYACCEPTED:
				currentScene->finishSending = true;
				break;
			case PROTOCOLO::STARTGAME:
				//En caso de no estar llena la llenamos
				if (myGame.full == false)
				{
					packRecieve >> teamMateAux.id;
					packRecieve >> teamMateAux.posX;
					packRecieve >> teamMateAux.posY;

					myGame.players.push_back(teamMateAux);

					std::cout << "id :" << teamMateAux.id << " " << teamMateAux.posX << " " << teamMateAux.posY << std::endl;

					packRecieve >> teamMateAux.id;
					packRecieve >> teamMateAux.posX;
					packRecieve >> teamMateAux.posY;
					myGame.players.push_back(teamMateAux);
					std::cout << "id :" << teamMateAux.id << " " << teamMateAux.posX << " " << teamMateAux.posY << std::endl;
					posX = teamMateAux.posX;
					posY = teamMateAux.posY;
				}
				//Hacemos send de vuelta para que pare de enviar el critico.
				packRecieve.clear();
				packRecieve << PROTOCOLO::STARTGAMEACCEPTED;
				if (socket.send(packRecieve, proxy.IP_Adress, proxy.port) == sf::Socket::Done)
				{
					//currentScene->CloseWindow();
					std::cout << "Empieza partida " << std::endl;
					currentScene->finishSending = true;
					sceneState = TypeScene::GOTO_PLAY;
				}
					//Ponerme a mi
				break;
			case PROTOCOLO::MOVEMENT:
			{
				packRecieve >> auxint;
				if (auxint >= 0)
				{
					myGameScene->myCharacter->cleanAccumMovement(auxint);
				}
				else
				{
					//Caso que nos impide
				}
				break;
			}
			case PROTOCOLO::TEAMPOSITION:
			{
				packRecieve >> auxint;
				packRecieve >> posX;
				packRecieve >> posY;
				
				//Actualizar Posicion avatrares
				//
				//
				//
				//////////////////////////////
				break;
			}
			default:
				break;
			}
		}
	}
}

//////////////////////////////////////////
////////////////////////////////////////// CLIENT
//////////////////////////////////////////
void clienteMain()
{
	////  ------------- MENSAJE --------------- ////
	//sf::Packet pack;

	socket.setBlocking(true);

	////////Nos guardamos la IP y el puerto del Server
	proxy.IP_Adress = IP_CLASE;
	proxy.port = PORT;

	//THREAD RECEIVE
	std::thread threadClient(&ClientReceive);
	threadClient.detach();

	////////////////////////////////para protocolo
	pack << PROTOCOLO::HELLO;

	///////////////////////////////////////////////////conectamos con el server
	sf::Socket::Status statusConfirmation = sf::Socket::NotReady;

	startTime = clock();
	//// ESTO SE TIENE QUE HACER CADA X TIEMPO
	while (!helloMessage)
	{
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;

		if (timeInSeconds >= 1)
		{
			startTime = clock();

			//mutex.lock();
			statusConfirmation = socket.send(pack, proxy.IP_Adress, proxy.port);
			std::cout << "ENVIO\n";
			//mutex.unlock();

			if (statusConfirmation != sf::Socket::Done)
			{
				std::cout << "No se ha podido enviar el mensaje" << std::endl;
			}
			else
			{
				std::cout << "Se ha enviado el mensaje" << std::endl;
			}
		}

	}
	

	///////condición del bucle 
	bool finish = false;

	std::string answer;
	int myCharacterType;

	sceneState = TypeScene::FIRST_CHOICE;

	currentScene = new FirstChoice(1);
	CharacterType auxType;
	while (finish == false)
	{
		//////////Switch de los estados de las escenes
		switch (sceneState)
		{
		case FIRST_CHOICE:
			sceneState = currentScene->DrawScene();
			break;

		case LOG_IN:
			currentScene->DrawScene();
			break;

		case SIGN_UP:

			currentScene->DrawScene();
			break;

		case MENU:

			sceneState = currentScene->DrawScene();
			break;

		case MAPS:
			currentScene->DrawScene();
			break;

		case PLAY:
			currentScene->DrawScene();
			break;

		case EXIT:
			finish = true;
			break;

		case GOTO_FIRST_CHOICE:
			std::cout << "Nos vamos a la escena First Choice" << std::endl;
			sceneState = TypeScene::FIRST_CHOICE;
			currentScene = new FirstChoice(1);
			currentScene->me = proxy;
			break;
		case GOTO_LOG_IN:
			std::cout << "Nos vamos a la escena Log In" << std::endl;
			sceneState = TypeScene::LOG_IN;
			currentScene = new LogIn(1, &socket);
			currentScene->me = proxy;
			break;

		case GOTO_SIGN_UP:
			std::cout << "Nos vamos a la escena Sign Up" << std::endl;
			sceneState = TypeScene::SIGN_UP;
			currentScene = new SignUp(1, &socket);
			currentScene->me = proxy;
			break;
		case GOTO_MENU:
			std::cout << "Nos vamos a la escena del Menu" << std::endl;
			sceneState = TypeScene::MENU;
			currentScene = new Menu(1);
			currentScene->me = proxy;
			break;
		case GOTO_MAPS:
			std::cout << "Nos vamos a la escena de Mapas" << std::endl;
			sceneState = TypeScene::MAPS;
			currentScene = new Maps(1, &socket);
			currentScene->me = proxy;
			break;
		case GOTO_PLAY:
			std::cout << "Nos vamos a la escena del Juego" << std::endl;
			sceneState = TypeScene::PLAY;
			auxType = static_cast<CharacterType>(proxy.skin);
			currentScene = myGameScene = new Game(auxType,posX,posY, &socket);
			
			currentScene->me = proxy;
			break;
		default:
			break;
		}
	}

	/*std::cout << "Escoge un personaje del 1 al 8: \n" << std::endl;
	std::cin >> answer;

	if (answer == "1")myCharacterType = 1;
	else if (answer == "2")myCharacterType = 2;
	else if (answer == "3")myCharacterType = 3;
	else if (answer == "4")myCharacterType = 4;
	else if (answer == "5")myCharacterType = 5;
	else if (answer == "6")myCharacterType = 6;
	else if (answer == "7")myCharacterType = 7;
	else if (answer == "8")myCharacterType = 8;*/

	//currentScene = new Game(static_cast<CharacterType>(myCharacterType));

	//currentScene->DrawScene();	
}

void main()
{
	sf::Packet prueba;

	prueba << "Funciona\n";
	int aux = 1;

	

	std::string answer;
	bool rightAnswer = false;

	while (!rightAnswer)
	{
		std::cout << "Quieres ser Server o Cliente? [s/c] " << std::endl;
		std::cin >> answer;
		if (answer == "c" || answer == "C" || answer == "s" || answer == "S" )
		{
			rightAnswer = true;
		}
	}

	if (answer == "c" || answer == "C")
	{
		std::cout << "Has escogido ser un cliente" << std::endl;
		clienteMain();
		
	}
	else if (answer == "s" || answer == "S")
	{
		std::cout << "Has escogido ser el servidor" << std::endl;
		serverMain();
	}
	
	
	
}
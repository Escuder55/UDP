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

	std::vector<PlayerProxy> players;
};

std::vector<gameProxy> gamesProxy;

int games = 0;
gameProxy auxGame;

/////////////////////MUTEX
std::mutex mutex;


//THREAD RECEIVE SERVER
void ServerReceive()
{
	int numPlayers = 0;
	//// ------------------------ MENSAJE RECIBIDO ----------------- ////
	PlayerProxy auxPlayerProxy;
	PROTOCOLO orders;
	sf::IpAddress adress;
	unsigned short port;

	//// ------------- BASE DE DATOS ------------------ //
	sql::SQLString HOSTBD = "tcp://www.db4free.net:3306";
	sql::SQLString USERNAMEBD = "puajklejos";
	sql::SQLString PASSWORDBD = "Puajklejos95*";
	sql::SQLString DATABASEBD = "practicaredes";
	//BD BaseDatos(HOSTBD, USERNAMEBD, PASSWORDBD, DATABASEBD);
	BD BaseDatos(HOSTBD, USERNAMEBD, PASSWORDBD, DATABASEBD);
	// VARIABLES BASE DE DATOS
	sql::SQLString SQLusername;
	sql::SQLString SQLpassword;
	std::string skin;
	int SQLSkin;
	//// ------------------------- SET MAPS --------------------- ////
	MapaGame map1;
	MapaGame map2;
	MapaGame map3;

	map1 = BaseDatos.getMap1();
	map2 = BaseDatos.getMap2();
	map3 = BaseDatos.getMap3();

	//// --------------------- BINARY TREES -------------------- ////
	BinaryTree BST;

	//PRUEBAS BASE DATOS
	/*int a = 1;
	std::cout << "MAP1 " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Sala" << i + a << ": " << std::endl;
		for (int j = 0; j < 4; j++)
		{
			std::cout << map1.salas[i].puertas[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "MAP2 " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Sala" << i + a << ": " << std::endl;
		for (int j = 0; j < 4; j++)
		{
			std::cout << map2.salas[i].puertas[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "MAP3 " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Sala" << i + a << ": " << std::endl;
		for (int j = 0; j < 4; j++)
		{
			std::cout << map3.salas[i].puertas[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/


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

			std::cout << "Adress: " << adress << std::endl;
			std::cout << "Port: " << port << std::endl;
			//PROTOCOLO A DAR
			int auxOrder;			

			pack >> auxOrder;
			orders = static_cast<PROTOCOLO>(auxOrder);

			//COMPROBACION
			
			std::cout << "He recibido lo siguiente: "  << auxOrder << std::endl;

			bool newPlayer = true;
			int currentId;

			switch (orders)
			{
			case PROTOCOLO::HELLO:
			{
				//////////////////////////////////////////////////comprobamos si este usuario ya ha enviado más hello
				for (int i = 0; i < playersConnecteds.size(); i++)
				{
					if (playersConnecteds[i].IP_Adress == adress && playersConnecteds[i].port == port)
					{
						newPlayer = false;
						currentId = i;
					}
				}

				orders = PROTOCOLO::WELCOME;


				/////////////////si el usuario es nuevo
				if (newPlayer)
				{
					numPlayers++;
					//GUARDAMOS INFO DE CONEXION DEL PLAYER
					auxPlayerProxy.IP_Adress = adress;
					auxPlayerProxy.port = port;
					auxPlayerProxy.id = numPlayers;
					playersConnecteds.push_back(auxPlayerProxy);

					pack.clear();
					pack << orders;
					pack << auxPlayerProxy.id;

					if (socket.send(pack, playersConnecteds[numPlayers - 1].IP_Adress, playersConnecteds[numPlayers - 1].port) == sf::Socket::Done)
					{
							
						std::cout << "Se ha enviado bien el WELCOME a la puerto: " << playersConnecteds[numPlayers - 1].port << std::endl;
					}
					std::cout << " Se ha recibido un nuevo cliente." << std::endl;
				}
				else
				{
					std::cout << "Se ha enviado bien el WELCOME a la puerto: " << playersConnecteds[currentId].port << std::endl;
					std::cout << "El Cliente ya existe." << std::endl;
					pack.clear();
					pack << orders << playersConnecteds[currentId].id;
					socket.send(pack, playersConnecteds[currentId].IP_Adress, playersConnecteds[currentId].port);
				}


				break;
			}
			case PROTOCOLO::REGISTER:
			{
				pack >> auxId;
				pack >> auxIdPacket;
				pack >> username;
				pack >> password;
				pack >> repeatPassword;
				pack >> skin;

				YouCanSignUp = false;

				if (password == repeatPassword)
				{
					SQLusername = username.c_str();
					SQLpassword = password.c_str();
					SQLSkin = std::atoi(skin.c_str());

					//COMPROVACION
					std::cout << "Register with User:		" << username << std::endl;
					std::cout << "Register with Password:	" << password << std::endl;
					std::cout << "Register with Skin:	" << skin << std::endl;

					//CONSULTA 
					YouCanSignUp = !BaseDatos.CheckUser(SQLusername);
					std::cout << "El usuario puede registrarse? " << YouCanSignUp << std::endl;

					if (YouCanSignUp)
					{
						BaseDatos.InsertNewUser(SQLusername, SQLpassword, SQLSkin);

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
					}
				}


				//SEND TO CLIENT
				pack.clear();
				pack << PROTOCOLO::REGISTERACCEPTED << auxPlayerProxy.id << YouCanSignUp;
				socket.send(pack, playersConnecteds[numPlayers - 1].IP_Adress, playersConnecteds[numPlayers - 1].port);
				break;
			}
			case PROTOCOLO::LOGIN:
			{
				
				
				playersConnecteds[getId(adress, port)].Critic_Message.insert({PROTOCOLO::LOGIN, Mensaje(playersConnecteds[getId(adress, port)].counterPacket, pack)});
				pack >> auxId;
				pack >> auxIdPacket;
				pack >> username;
				pack >> password;

				SQLusername = username.c_str();
				SQLpassword = password.c_str();

				std::cout << "He recibido un intento de Login." << std::endl;
				//COMPROVACION
				for (int i = 0; i < playersConnecteds.size(); i++)
				{
					if (playersConnecteds[i].id == auxId)
					{
						std::cout << "El usuario con id: " << auxId
							<< "Ha enviado el paquete con id: " << auxIdPacket
							<< "Log in User:		" << username << std::endl;
						std::cout << "Log in Password:	" << password << std::endl;

						//CONSULTA 
						YouCanLogin = BaseDatos.LoginUser(SQLusername, SQLpassword);
						std::cout << "El usuario puede entrar? " << YouCanLogin << std::endl;

						playersConnecteds[i].skin = BaseDatos.TakeSkin(SQLusername, SQLpassword);

						//SEND TO CLIENT
						pack.clear();
						pack << PROTOCOLO::LOGINACCEPTED << auxPlayerProxy.id << YouCanLogin << playersConnecteds[i].skin;
						socket.send(pack, playersConnecteds[i].IP_Adress, playersConnecteds[i].port);

					}
					else
					{
						std::cout << "he recibido el intento de login pero no coincie con ningun usuario " << std::endl;
					}

				}
				break;
			}
			case PROTOCOLO::WANTPLAY:
			{
				for (int i = 0; i < playersConnecteds.size(); )
				{

				}
				if (gamesProxy.size() == 0)
				{					

					//gamesProxy.pushback(auxGame);
				}
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
}
//THREAD PAQUETES CRÍTICOS
void SendCriticPack()
{
	int iterador = 0 ;
	int aux = 0;
	PROTOCOLO auxProtocolo= PROTOCOLO::NONEPROTOCOLO;
	while (true)
	{
		if (!playersConnecteds.empty())
		{
			if (!playersConnecteds[iterador].Critic_Message.empty())
			{
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::LOGIN))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::LOGIN);
					auxProtocolo = PROTOCOLO::LOGIN;
					std::cout << "1" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::REGISTER))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::REGISTER);
					auxProtocolo = PROTOCOLO::REGISTER;
					std::cout << "2" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::ROOMCHANGE))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::ROOMCHANGE);
					auxProtocolo = PROTOCOLO::ROOMCHANGE;
					std::cout << "3" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::DISCONECTED))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::DISCONECTED);
					auxProtocolo = PROTOCOLO::DISCONECTED;
					std::cout << "4" << std::endl;
				}
				if (aux < playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::WANTPLAY))
				{
					aux = playersConnecteds[iterador].Critic_Message.count(PROTOCOLO::WANTPLAY);
					auxProtocolo = PROTOCOLO::WANTPLAY;
					std::cout << "5" << std::endl;
				}

				switch (auxProtocolo)
				{
				case REGISTER:
					break;
				case LOGIN:
					std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
					break;
				case WANTPLAY:
					break;
				case STARTGAME:
					break;
				case ROOMCHANGE:
					break;
				case DISCONECTED:
					break;
				default:
					std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
					break;
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

	std::thread threadCritic(&SendCriticPack);
	threadCritic.detach();
	while (1)
	{

	}
}

//THREAD RECEIVE CLIENT
void ClientReceive()
{
	sf::IpAddress auxIP;
	unsigned short auxport;
	sf::Packet packRecieve;
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
			std::cout << "Se ha recibido el mensaje" << std::endl;
			//RECOGEMOS VARIABLES
			int auxOrder;
			packRecieve >> auxOrder;
			packRecieve >> proxy.id;

			orders = static_cast<PROTOCOLO>(auxOrder);

			switch (orders)
			{
			case PROTOCOLO::WELCOME:
				helloMessage = true;
				std::cout << "El servidor te da la bienvenida con el siguiente id: " << proxy.id << std::endl;
				break;
			case PROTOCOLO::LOGINACCEPTED:
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
			sceneState = currentScene->DrawScene();
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
			currentScene = new Game(auxType);
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
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

//MENSAJES CRITICOS
//std::list<std::stack<Mensaje>> paquetes_criticos;

//MENSAJES NORMALES
//std::list<std::stack<Mensaje>> paquetes_normales;

//LOGIN/REGISTER
bool YouCanLogin;
bool YouCanSignUp;
int auxId;
int auxIdPacket;

////////puntero a la escena actual
Scene* currentScene;




//THREAD RECEIVE SERVER
void ServerReceive()
{
	int numPlayers = 0;
	//// ------------------------ MENSAJE RECIBIDO ----------------- ////
	PlayerProxy auxPlayerProxy;
	PROTOCOLO orders;
	sf::Packet pack;
	sf::IpAddress adress;
	unsigned short port;

	//// ------------- BASE DE DATOS ------------------ //
	sql::SQLString HOSTBD = "tcp://www.db4free.net:3306";
	sql::SQLString USERNAMEBD = "puajklejos";
	sql::SQLString PASSWORDBD = "Puajklejos95*";
	sql::SQLString DATABASEBD = "practicaredes";
	BD BaseDatos(HOSTBD, USERNAMEBD, PASSWORDBD, DATABASEBD);
	// VARIABLES BASE DE DATOS
	sql::SQLString SQLusername;
	sql::SQLString SQLpassword;
	std::string skin;
	int SQLSkin;

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

					pack << orders << auxPlayerProxy.id;
					socket.send(pack, playersConnecteds[numPlayers - 1].IP_Adress, playersConnecteds[numPlayers - 1].port);
				}
				else
				{
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

	while (1)
	{

	}
}

//THREAD RECEIVE CLIENT
void ClientReceive()
{
	while (true)
	{
		//COMPROBACION
		sf::Socket::Status status;
		status = socket.receive(pack, proxy.IP_Adress, proxy.port);
		if (status != sf::Socket::Done)
		{
			std::cout << "No se ha podido recibir el mensaje" << std::endl;
		}
		else
		{
			std::cout << "Se ha recibido el mensaje" << std::endl;
			//RECOGEMOS VARIABLES
			int auxOrder;
			pack >> auxOrder;
			pack >> proxy.id;

			orders = static_cast<PROTOCOLO>(auxOrder);

			switch (orders)
			{
			case PROTOCOLO::WELCOME:
				std::cout << "El servidor te da la bienvenida con el siguiente id: " << proxy.id << std::endl;
				break;
			case PROTOCOLO::LOGINACCEPTED:
				pack >> YouCanLogin;
				std::cout << "Me puedo conectar: " << YouCanLogin << std::endl;
				if (YouCanLogin)
				{					
					pack >> proxy.skin;
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
				pack >> YouCanSignUp;
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
	sf::Packet pack;

	////////Nos guardamos la IP y el puerto del Server
	proxy.IP_Adress = IP_CLASE;
	proxy.port = PORT;

	////////////////////////////////para protocolo
	pack << PROTOCOLO::HELLO;

	///////////////////////////////////////////////////conectamos con el server
	sf::Socket::Status statusConfirmation = sf::Socket::NotReady;

	//// ESTO SE TIENE QUE HACER CADA X TIEMPO
	while (statusConfirmation != sf::Socket::Done)
	{
		statusConfirmation = socket.send(pack, proxy.IP_Adress, proxy.port);
		if (status != sf::Socket::Done)
		{
			std::cout << "No se ha podido enviar el mensaje" << std::endl;
		}
		else
		{
			std::cout << "Se ha enviado el mensaje" << std::endl;
		}

	}
	
	//THREAD RECEIVE
	std::thread threadClient(&ClientReceive);
	threadClient.detach();

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
			sceneState = currentScene->DrawScene();
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
			currentScene = new Maps(1);
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
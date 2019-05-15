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


/////////////////////////////////////////// VARIABLES COMPARTIDAS
PROTOCOLO orders;

//////////////////////////////////////////	VARIABLES PARA EL CLIENTE
sf::Socket::Status status;
sf::Packet pack;
sf::UdpSocket socket;

//////////////////////////////////////////	VARIABLES PARA EL SERVER
//PLAYER PROXIES
std::vector<PlayerProxy> playersConnecteds;

//MENSAJES CRITICOS
std::list<std::stack<Mensaje>> paquetes_criticos;

//MENSAJES NORMALES
std::list<std::stack<Mensaje>> paquetes_normales;


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

	std::cout << "ENTRO EN EL THREAD" << std::endl;

	while (numPlayers < 3)
	{

		status = socket.receive(pack, adress, port);	

		if (status == sf::Socket::Done)
		{
			std::cout << "Adress: " << adress << std::endl;
			std::cout << "Port: " << port << std::endl;
			//PROTOCOLO A DAR
			int auxOrder;
			pack >> auxOrder;
			orders = static_cast<PROTOCOLO>(auxOrder);

			//COMPROBACION
			std::cout << "He recibido lo siguiente: "  << auxOrder << std::endl;

			switch (orders)
			{
			case PROTOCOLO::HELLO:
				numPlayers++;
				//GUARDAMOS INFO DE CONEXION DEL PLAYER
				auxPlayerProxy.IP_Adress = adress;
				auxPlayerProxy.port = port;
				auxPlayerProxy.id = numPlayers;
				playersConnecteds.push_back(auxPlayerProxy);
				pack.clear();

				orders = PROTOCOLO::WELCOME;

				pack << orders << auxPlayerProxy.id;
				socket.send(pack, playersConnecteds[numPlayers - 1].IP_Adress, playersConnecteds[numPlayers - 1].port);
					break;

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

}

//////////////////////////////////////////
////////////////////////////////////////// CLIENT
//////////////////////////////////////////
void clienteMain()
{
	////  ------------- PROXY --------------- ////
	PlayerProxy proxy;

	////  ------------- MENSAJE --------------- ////
	sf::Packet pack;

	////////Nos guardamos la IP y el puerto del Server
	proxy.IP_Adress = IP_CLASE;
	proxy.port = PORT;

	////////////////////////////////para protocolo
	pack << PROTOCOLO::HELLO;

	///////////////////////////////////////////////////conectamos con el server
	sf::Socket::Status statusConfirmation = sf::Socket::NotReady;

	while (statusConfirmation != sf::Socket::Done)
	{
		status = socket.send(pack, proxy.IP_Adress, proxy.port);
		if (status != sf::Socket::Done)
		{
			std::cout << "No se ha podido enviar el mensaje" << std::endl;
		}
		else
		{
			std::cout << "Se ha enviado el mensaje" << std::endl;


			//COMPROBACION

			statusConfirmation = socket.receive(pack, proxy.IP_Adress, proxy.port);
			if (statusConfirmation != sf::Socket::Done)
			{
				std::cout << "No se ha podido recibir el mensaje" << std::endl;
			}
			else
			{
				std::cout << "Se ha recibido el mensaje" << std::endl;
			}
		}

	}
	

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
		default:
		break;
	}

	//THREAD RECEIVE
	std::thread threadClient(&ClientReceive);
	threadClient.detach();

	///////condición del bucle 
	bool finish = false;

	////////puntero a la escena actual
	Scene* currentScene;

	std::string answer;
	int myCharacterType;

	TypeScene sceneState = TypeScene::FIRST_CHOICE;

	currentScene = new FirstChoice(1);
	while (finish == false)
	{


		//////////Switch de los estados de las escenes
		switch (sceneState)
		{
		case FIRST_CHOICE:
			sceneState = currentScene->DrawScene();
			break;

		case LOG_IN:
			sceneState = currentScene->DrawScene();
			break;

		case SIGN_UP:

			sceneState = currentScene->DrawScene();
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
			break;
		case GOTO_LOG_IN:
			std::cout << "Nos vamos a la escena Log In" << std::endl;
			sceneState = TypeScene::LOG_IN;
			currentScene = new LogIn(1);
			break;

		case GOTO_SIGN_UP:
			std::cout << "Nos vamos a la escena Sign Up" << std::endl;
			sceneState = TypeScene::SIGN_UP;
			currentScene = new SignUp(1);
			break;
		case GOTO_MENU:
			std::cout << "Nos vamos a la escena del Menu" << std::endl;
			sceneState = TypeScene::MENU;
			currentScene = new Menu(1);
			break;
		case GOTO_MAPS:
			std::cout << "Nos vamos a la escena de Mapas" << std::endl;
			sceneState = TypeScene::MAPS;
			currentScene = new Maps(1);
			break;
		case GOTO_PLAY:
			std::cout << "Nos vamos a la escena del Juego" << std::endl;
			sceneState = TypeScene::PLAY;
			currentScene = new Game(CharacterType::EIGHT);
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
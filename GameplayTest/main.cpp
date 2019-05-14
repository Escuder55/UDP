#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
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

//////////////////////////////////////////	VARIABLES PARA EL CLIENTE
sf::Socket::Status status;
sf::Packet pack;
sf::UdpSocket socket;

//////////////////////////////////////////	VARIABLES PARA EL SERVER
struct players
{
	sf::IpAddress IP_Adress;
	unsigned int port;
	int id;
	int posX;
	int posY;
};

std::vector<players> playersConnecteds;
//////////////////////////////////////////
////////////////////////////////////////// CLIENT
//////////////////////////////////////////
void clienteMain()
{
	////////Nos guardamos la IP y el puerto del Server
	sf::IpAddress adreesServer = IP_CLASE;
	unsigned short port = PORT;

	////////////////////////////////para protocolo
	std::string protocolo = "HELLO";
	std::string name;

	std::cout << "Write your name" << std::endl;
	std::cin >> name;

	pack << protocolo << name;

	///////////////////////////////////////////////////conectamos con el server
	status = socket.send(pack, adreesServer, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "No se ha podido enviar el mensaje" << std::endl;
	}

	status = socket.receive(pack, adreesServer, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "No se ha podido enviar el mensaje" << std::endl;
	}
	int idPlayer;

	pack >> protocolo >> idPlayer >> name;

	if (protocolo == "WELCOME")
	{
		std::cout << "El servidor te da la bienvenida " << name << " y te asigna la siguiente ID: " << idPlayer << std::endl;
	}


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


//////////////////////////////////////////
////////////////////////////////////////// SERVER
//////////////////////////////////////////
void serverMain()
{
	sf::UdpSocket socket;
	sf::Socket::Status status;

	status = socket.bind(PORT);
	if (status != sf::Socket::Done)
	{
		std::cout << "no se puede hacer bind bien con el puerto 50000" << std::endl;
	}
	int numPlayers = 0;
	////////////////////////////////varibles protocolo
	std::string protocolo;
	std::string name;
	sf::Packet pack;
	sf::IpAddress adress;
	unsigned short port;

	while (numPlayers < 3)
	{
		status = socket.receive(pack, adress, port);
		if (status == sf::Socket::Done)
		{

			pack >> protocolo;
			if (protocolo == "HELLO")
			{
				numPlayers++;
				playersConnecteds.push_back({ adress, port ,numPlayers, numPlayers, numPlayers });

				pack >> name;

				std::cout << "Welcome To " << name << std::endl;

				pack.clear();

				protocolo = "WELCOME";
				int id = numPlayers;

				pack << protocolo << id << name;				
				socket.send(pack, playersConnecteds[numPlayers - 1].IP_Adress, playersConnecteds[numPlayers - 1].port);
			}

		}
	}

	while (true)
	{

	}
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
		clienteMain();
	}
	else if (answer == "s" || answer == "S")
	{
		serverMain();
	}
	
	
	
}
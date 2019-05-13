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



void main()
{
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
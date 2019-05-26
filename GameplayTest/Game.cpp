#include "Game.h"



Game::Game()
{
	
}

Game::Game(CharacterType myCharacterType, float _posX, float _posY, sf::UdpSocket *sock, int skin)
{
	startTime = clock();
	//Guardamos socket
	socket = sock;
	/////////////////////////////////////////////inicializaciones temporales,para probar cosas
	doorsOpen = false;
	currentBackground = 0;

	posPartnerX = _posX;
	posPartnerY = _posY;
	partnerSkin = skin;

	//Ghosts Init//////////////////////
	AddGhots((DOOR_LEFT_POS_X + 45) + 230.f, 160.f, 1, 0);
	AddGhots((DOOR_LEFT_POS_X + 45) + 400.f, 270.f, 2, 0);
	AddGhots((DOOR_LEFT_POS_X + 45) + 250.f, 100.f, 3, 1);
	AddGhots((DOOR_LEFT_POS_X + 45) + 100.f, 350.f, 4, 2);
	AddGhots((DOOR_LEFT_POS_X + 45) + 500.f, 350.f, 5, 3);

	/////////////////////////////////////////////inicializamos el Character con el typo que le hayamos pasado,
	/////////////////////////////////////////////en un futuro esta inicialización tendrá que ser con la skin que 
	/////////////////////////////////////////////tenga el jugador en su base de datos
	myCharacter = new Character(myCharacterType, sock);

	//////////////////////////////////////////cargamos todos los sprites
	InitSprites();
	InitWindow();
}

Game::~Game()
{
}

void Game::InitSprites()
{
	////////////////////////////////////////////////////////////////////////BACKGROUNDS
	switch (partnerSkin)
	{
	case 1:
		if (!partnerTexture.loadFromFile("res/img/Character1.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 2:
		if (!partnerTexture.loadFromFile("res/img/Character2.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 3:
		if (!partnerTexture.loadFromFile("res/img/Character3.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 4:
		if (!partnerTexture.loadFromFile("res/img/Character4.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}

		break;
	case 5:
		if (!partnerTexture.loadFromFile("res/img/Character5.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 6:
		if (!partnerTexture.loadFromFile("res/img/Character6.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 7:
		if (!partnerTexture.loadFromFile("res/img/Character7.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	case 8:
		if (!partnerTexture.loadFromFile("res/img/Character8.png"))
		{
			std::cout << "Cannot Load the image" << std::endl;
		}
		break;
	default:
		break;
	}
	
	partner.setTexture(partnerTexture);
	partner.setPosition(posPartnerX, posPartnerY);
	//partner.setScale(sf::Vector2f(0.5, 0.5));


		///////////////////BACKGROUND 1
	if (!bgTexture[0].loadFromFile("res/img/Sala1.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[0].setTexture(bgTexture[0]);
	background[0].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[0].setScale(sf::Vector2f(0.5, 0.5));

	///////////////////BACKGROUND 2
	if (!bgTexture[1].loadFromFile("res/img/Sala2.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[1].setTexture(bgTexture[1]);
	background[1].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[1].setScale(sf::Vector2f(0.5, 0.5));

	///////////////////BACKGROUND 2
	if (!bgTexture[2].loadFromFile("res/img/Sala3.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[2].setTexture(bgTexture[2]);
	background[2].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[2].setScale(sf::Vector2f(0.5, 0.5));
	///////////////////BACKGROUND 2
	if (!bgTexture[3].loadFromFile("res/img/Sala4.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[3].setTexture(bgTexture[3]);
	background[3].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[3].setScale(sf::Vector2f(0.5, 0.5));
			   
	////////////////////////////////////////////////////////////////////////DOORS

		////////////UP DOOR
	if (!doorTexture[0].loadFromFile("res/img/ClosedDoorUp.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	doors[0].setTexture(doorTexture[0]);
	doors[0].setPosition(sf::Vector2f(DOOR_UP_POS_X, DOOR_UP_POS_Y));
	doors[0].setScale(sf::Vector2f(0.5, 0.5));

	////////////RIGHT DOOR
	if (!doorTexture[1].loadFromFile("res/img/ClosedDoorRight.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	doors[1].setTexture(doorTexture[1]);
	doors[1].setPosition(sf::Vector2f(DOOR_RIGHT_POS_X, DOOR_RIGHT_POS_Y));
	doors[1].setScale(sf::Vector2f(0.5, 0.5));
	////////////RIGHT DOOR
	if (!doorTexture[2].loadFromFile("res/img/ClosedDoorDown.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	doors[2].setTexture(doorTexture[2]);
	doors[2].setPosition(sf::Vector2f(DOOR_DOWN_POS_X, DOOR_DOWN_POS_Y));
	doors[2].setScale(sf::Vector2f(0.5, 0.5));

	////////////RIGHT DOOR
	if (!doorTexture[3].loadFromFile("res/img/ClosedDoorLeft.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	doors[3].setTexture(doorTexture[3]);
	doors[3].setPosition(sf::Vector2f(DOOR_LEFT_POS_X, DOOR_LEFT_POS_Y));
	doors[3].setScale(sf::Vector2f(0.5, 0.5));

}

TypeScene Game::DrawScene()
{
	sf::Socket::Status status;
	while (window.isOpen())
	{
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		///////////////////////////////////limpiamos la pantalla
		window.clear();
		///////////////////////////////////pintamos background y puertas de momento
		DrawSprites();
		///////////////////////////////////controlamos los inputs antes de pintar el personaje por si hay que modificarlo
		InputControl(&window);
		///////////////////////////////////el character se pinta a si mismo
		myCharacter->DrawCharacter(&window);
		switch (mySala)
		{
		case 0:
		{
			if (myCharacter->changeRoomToLeft || myCharacter->changeRoomToUp)
			{
				myCharacter->changeRoomToLeft = false;
				myCharacter->changeRoomToUp = false;
			}
			if (myCharacter->changeRoomToDown)
			{
				if (timeInSeconds > 1) 
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 2;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}
			}
			else if (myCharacter->changeRoomToRight)
			{
				if (timeInSeconds > 1)
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 1;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}
			}
			break;
		}
		case 1:
		{
			if (myCharacter->changeRoomToLeft)
			{
				if (timeInSeconds > 1)
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 0;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}
			}
			if (myCharacter->changeRoomToRight || myCharacter->changeRoomToDown || myCharacter->changeRoomToUp)
			{
				myCharacter->changeRoomToRight = false;
				myCharacter->changeRoomToDown = false;
				myCharacter->changeRoomToUp = false;
			}
			break;
		}
		case 2:
		{
			if (myCharacter->changeRoomToRight)
			{
				if (timeInSeconds > 1)
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 3;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}

				break;
			}
			else if (myCharacter->changeRoomToUp)
			{
				if (timeInSeconds > 1)
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 0;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}
			}
			if (myCharacter->changeRoomToLeft || myCharacter->changeRoomToDown)
			{
				myCharacter->changeRoomToLeft = false;
				myCharacter->changeRoomToDown = false;
			}
		}
		case 3:
		{
			if (myCharacter->changeRoomToLeft)
			{
				if (timeInSeconds > 1)
				{
					startTime = clock();
					GamePack.clear();
					GamePack << PROTOCOLO::ROOMCHANGE;
					GamePack << 2;

					status = socket->send(GamePack, IP_CLASE, PORT);
					if (status == sf::Socket::Status::Done)
					{
						std::cout << "Se ha enviado que me muevo a la sala 1" << std::endl;
					}
				}
			}
			if (myCharacter->changeRoomToRight || myCharacter->changeRoomToDown || myCharacter->changeRoomToUp)
			{
				myCharacter->changeRoomToRight = false;
				myCharacter->changeRoomToDown = false;
				myCharacter->changeRoomToUp = false;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		DrawEnemies();

		window.display();
	}
	
	return myTypeScene;
}

void Game::InputControl(sf::RenderWindow * window)
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
				CloseWindow();
			break;
		case sf::Event::KeyPressed:
				////////////////////le pasamos al Character que tecla se ha apretado
				myCharacter->UpdateCharacterPosition(event.key.code,true);
				////////////////////////////////////////////////////////////////PRESIONAR ESCAPE
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				////////////////////////////////////////////////////////////////PRESIONAR ENTER
				else if (event.key.code == sf::Keyboard::Return)
				{
					if (doorsOpen)doorsOpen = false;
					else doorsOpen = true;
				}
				////////////////////////////////////////////////////////////////PRESIONAR NUMEROS
				else if (event.key.code == sf::Keyboard::Num1)
				{
					currentBackground = 0;
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					currentBackground = 1;
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					currentBackground = 2;
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					currentBackground = 3;
				}
			break;
		case sf::Event::KeyReleased:
			////////////////////////////////////comprobamos si se deja de apretar alguna de las teclas
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Right||
					event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left||
					event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::W ||
					event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
				{
					myCharacter->UpdateCharacterPosition(event.key.code, false);
				}
			break;
		default:
			break;
		}
		
	}
}

void Game::DrawSprites()
{		
	window.draw(background[mySala]);	
	///////////////////////////PINTANDO LAS PUERTAS
	if (!doorsOpen)
	{
		for (int i = 0; i < 4; i++)
		{
			//window.draw(doors[i]);
		}
	}
	if (partnerSala == mySala)
	{
		window.draw(partner);
	}	
}

void Game::DrawEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->idSala == mySala)
		{
			enemies[i]->DrawGhost(&window);
		}
	}
}

void Game::AddGhots(float _posX, float _posY, int _ID, int _IDSala)
{
	Ghost *aux;
	aux = new Ghost(_posX, _posY, _IDSala, _ID);
	enemies.push_back(aux);
}
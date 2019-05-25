#include "Game.h"



Game::Game()
{
	
}

Game::Game(CharacterType myCharacterType, float _posX, float _posY, sf::UdpSocket *sock)
{
	//Guardamos socket
	socket = sock;
	/////////////////////////////////////////////inicializaciones temporales,para probar cosas
	doorsOpen = false;
	currentBackground = 0;

	posPartnerX = _posX;
	posPartnerY = _posY;

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

	if (!partnerTexture.loadFromFile("res/img/Partner.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	partner.setTexture(partnerTexture);
	partner.setPosition(posPartnerX, posPartnerY);
	//partner.setScale(sf::Vector2f(0.5, 0.5));


		///////////////////BACKGROUND 1
	if (!bgTexture[0].loadFromFile("res/img/Backgorund1.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[0].setTexture(bgTexture[0]);
	background[0].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[0].setScale(sf::Vector2f(0.5, 0.5));

	///////////////////BACKGROUND 2
	if (!bgTexture[1].loadFromFile("res/img/Backgorund2.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[1].setTexture(bgTexture[1]);
	background[1].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[1].setScale(sf::Vector2f(0.5, 0.5));

	///////////////////BACKGROUND 2
	if (!bgTexture[2].loadFromFile("res/img/Backgorund3.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	background[2].setTexture(bgTexture[2]);
	background[2].setPosition(sf::Vector2f(0.0f, 0.0f));
	background[2].setScale(sf::Vector2f(0.5, 0.5));

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
	while (window.isOpen())
	{
		
		///////////////////////////////////limpiamos la pantalla
		window.clear();
		///////////////////////////////////pintamos background y puertas de momento
		DrawSprites();
		///////////////////////////////////controlamos los inputs antes de pintar el personaje por si hay que modificarlo
		InputControl(&window);
		///////////////////////////////////el character se pinta a si mismo
		myCharacter->DrawCharacter(&window);

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
	
		
	window.draw(background[currentBackground]);	
	///////////////////////////PINTANDO LAS PUERTAS
	if (!doorsOpen)
	{
		for (int i = 0; i < 4; i++)
		{
			window.draw(doors[i]);
		}
	}
	window.draw(partner);
}

void Game::UpdatePartnerPosition(float _posX, float _posY)
{
	partner.setPosition(_posX,_posY);
}

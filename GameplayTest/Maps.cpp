#include "Maps.h"



Maps::Maps()
{
	InitSprites();
}

Maps::Maps(int i, sf::UdpSocket* _socket)
{
	socket = _socket;

	InitWindow();
	InitSprites();
}


Maps::~Maps()
{
}

void Maps::InitSprites()
{
	/////////////////////////////////////////////////////////////MAP 1
	if (!map1Texture.loadFromFile("res/img/Button_Map1.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	map1Sprite.setTexture(map1Texture);
	map1Sprite.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 200);

	/////////////////////////////////////////////////////////////MAP 2
	/*if (!map2Texture.loadFromFile("res/img/Button_Map2.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	map2Sprite.setTexture(map2Texture);
	map2Sprite.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);*/

	/////////////////////////////////////////////////////////////MAP 3
	/*if (!map3Texture.loadFromFile("res/img/Button_Map3.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	map3Sprite.setTexture(map3Texture);
	map3Sprite.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);*/

	///////////////////////////////////////////////////////////// BACK
	if (!backTexture.loadFromFile("res/img/Button_Back.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	backSprite.setTexture(backTexture);
	backSprite.setPosition(100, SCREEN_HEIGHT -100);
}

void Maps::DrawSprites()
{
	window.draw(map1Sprite);
	window.draw(map2Sprite);
	window.draw(map3Sprite);

	window.draw(backSprite);
}

TypeScene Maps::DrawScene()
{
	while (window.isOpen())
	{

		///////////////////////////////////limpiamos la pantalla
		window.clear();

		DrawSprites();
		////////////////////////////////////para el control de clicks
		InputControl(&window);

		window.display();
	}
	return myTypeScene;
}

int Maps::CheckButtonClicked(sf::Vector2f posClick)
{
	int button = 0;
	//////////////////////////comprobar el botton map1
	if (posClick.x >= map1Sprite.getPosition().x && posClick.x <= map1Sprite.getPosition().x + map1Sprite.getTextureRect().width &&
		posClick.y >= map1Sprite.getPosition().y && posClick.y <= map1Sprite.getPosition().y + map1Sprite.getTextureRect().height)
	{
		button = 1;
	}
	//////////////////////////comprobar el botton map 2
	else if (posClick.x >= map2Sprite.getPosition().x && posClick.x <= map2Sprite.getPosition().x + map2Sprite.getTextureRect().width &&
		posClick.y >= map2Sprite.getPosition().y && posClick.y <= map2Sprite.getPosition().y + map2Sprite.getTextureRect().height)
	{
		button = 2;
	}
	//////////////////////////comprobar el botton map 3
	else if (posClick.x >= map3Sprite.getPosition().x && posClick.x <= map3Sprite.getPosition().x + map3Sprite.getTextureRect().width &&
		posClick.y >= map3Sprite.getPosition().y && posClick.y <= map3Sprite.getPosition().y + map3Sprite.getTextureRect().height)
	{
		button = 3;
	}
	//////////////////////////comprobar el botton Back
	else if (posClick.x >= backSprite.getPosition().x && posClick.x <= backSprite.getPosition().x + backSprite.getTextureRect().width &&
		posClick.y >= backSprite.getPosition().y && posClick.y <= backSprite.getPosition().y + backSprite.getTextureRect().height)
	{
		button = 4;
	}

	return button;
}

void Maps::InputControl(sf::RenderWindow * window)
{
	sf::Event event;
	int buttonClicked = 0;
	sf::Vector2f mousePosition;

	sf::Packet pack;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			CloseWindow();
			break;
		case sf::Event::MouseButtonPressed:

			mousePosition.x = event.mouseButton.x;
			mousePosition.y = event.mouseButton.y;
			buttonClicked = CheckButtonClicked(mousePosition);

			switch (buttonClicked)
			{
			case 0:
				std::cout << "Ningun Boton" << std::endl;
				break;
			case 1:
				std::cout << "Se ha Clickado el Mapa 1" << std::endl;				
				pack << PROTOCOLO::WANTPLAY << 1 ; 
				sendPacket(pack, IP_CLASE, PORT);
				window->close();
				break;
			case 2:
				std::cout << "Se ha Clickado el Mapa 2" << std::endl;
				pack << PROTOCOLO::WANTPLAY << 2;
				sendPacket(pack, IP_CLASE, PORT);
				window->close();
				break;
			case 3:
				std::cout << "Se ha Clickado el Mapa 3" << std::endl;
				pack << PROTOCOLO::WANTPLAY << 3;
				sendPacket(pack, IP_CLASE, PORT);
				window->close();
				break;
			case 4:
				std::cout << "Se ha Clickado el boton Back" << std::endl;
				myTypeScene = TypeScene::GOTO_MENU;
				window->close();
				break;
			default:
				std::cout << "Ningun Boton" << std::endl;
				break;
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
				myTypeScene = TypeScene::EXIT;
			}
			break;
		default:
			break;
		}
	}
}

void Maps::sendPacket(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port)
{
	startTime = clock();

	while (!finishSending)
	{
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;

		if (timeInSeconds >= 0.5)
		{
			startTime = clock();
			sf::Socket::Status status = socket->send(pack, _IP, _port);

			if (status != sf::Socket::Done)
			{
				std::cout << "No se ha podido enviar el mensaje" << std::endl;
			}
			else
			{
				std::cout << "Se ha enviado el mensaje" << std::endl;
			}
		}
	}

}

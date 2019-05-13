#include "Menu.h"



Menu::Menu()
{
	InitSprites();
}

Menu::Menu(int i)
{
	InitWindow();
	InitSprites();
	InitText();
}


Menu::~Menu()
{
}

TypeScene Menu::DrawScene()
{
	while (window.isOpen())
	{

		///////////////////////////////////limpiamos la pantalla
		window.clear();

		DrawSprites();
		DrawText();
		////////////////////////////////////para el control de clicks
		InputControl(&window);

		window.display();
	}
	return myTypeScene;
}

void Menu::InitSprites()
{
	/////////////////////////////////////////////////////////////PLAY BUTTON
	if (!playTexture.loadFromFile("res/img/Button_Play.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	playButton.setTexture(playTexture);
	playButton.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);
	/////////////////////////////////////////////////////////////LOG OUT BUTTON
	if (!logOutTexture.loadFromFile("res/img/Button_LogOut.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	logOutButton.setTexture(logOutTexture);
	logOutButton.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 +50);
	/////////////////////////////////////////////////////////////EXIT BUTTON
	if (!exitTexture.loadFromFile("res/img/Button_Exit.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	exitButton.setTexture(exitTexture);
	exitButton.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150);

}

void Menu::InitText()
{
	if (!myFont.loadFromFile("res/fonts/courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE USER
	Title = "NEVER SPLIT THE PARTY";
	titleText.setString(Title);
	titleText.setFont(myFont);
	titleText.setCharacterSize(60);
	titleText.setFillColor(sf::Color(0, 200, 0));
	titleText.setStyle(sf::Text::Bold);
	titleText.setPosition(sf::Vector2f(100, 50));
}

void Menu::DrawSprites()
{
	window.draw(playButton);
	window.draw(logOutButton);
	window.draw(exitButton);
}

void Menu::DrawText()
{
	window.draw(titleText);
}

int Menu::CheckButtonClicked(sf::Vector2f posClick)
{
	int buttonClicked = 0;
	///////////////////comprobamos el botton play
	if (posClick.x >= playButton.getPosition().x && posClick.x <= playButton.getPosition().x + playButton.getTextureRect().width &&
		posClick.y >= playButton.getPosition().y && posClick.y <= playButton.getPosition().y + playButton.getTextureRect().height)
	{
		buttonClicked = 1;
	}
	/////////////////comprobamos el botton Log out
	else if (posClick.x >= logOutButton.getPosition().x && posClick.x <= logOutButton.getPosition().x + logOutButton.getTextureRect().width &&
			posClick.y >= logOutButton.getPosition().y && posClick.y <= logOutButton.getPosition().y + logOutButton.getTextureRect().height)
	{
		buttonClicked = 2;
	}
	/////////////////comprobamos el botton Exit
	else if (posClick.x >= exitButton.getPosition().x && posClick.x <= exitButton.getPosition().x + exitButton.getTextureRect().width &&
			posClick.y >= exitButton.getPosition().y && posClick.y <= exitButton.getPosition().y + exitButton.getTextureRect().height)
	{
		buttonClicked = 3;
	}


	return buttonClicked;
}

void Menu::InputControl(sf::RenderWindow * window)
{
	sf::Event event;
	sf::Vector2f mousePosition;
	int button;

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
			button = CheckButtonClicked(mousePosition);
			/////////////////////////combiaremos la escena en función de que botton se ha apretado
			if ( button== 1)
			{
				myTypeScene = TypeScene::GOTO_MAPS;
				window->close();
			}
			if (button == 2)
			{
				myTypeScene = TypeScene::GOTO_FIRST_CHOICE;
				window->close();
			}
			if (button == 3)
			{
				myTypeScene = TypeScene::EXIT;
				window->close();
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

#include "FirstChoice.h"



FirstChoice::FirstChoice()
{
}

FirstChoice::FirstChoice(int aux)
{

	InitWindow();
	InitSprites();
}


FirstChoice::~FirstChoice()
{
}

void FirstChoice::InitSprites()
{
	/////////////////////////////////////////////////////////////LOGIN BUTTON
	if (!logInTexture.loadFromFile("res/img/Button_LogIn.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	logInSprite.setTexture(logInTexture);
	logInSprite.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 150);

	/////////////////////////////////////////////////////////////SIGN UP BUTTON
	if (!signUpTexture.loadFromFile("res/img/Button_SignUp.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	signUpSprite.setTexture(signUpTexture);
	signUpSprite.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 +50);
}

int FirstChoice::CheckButtonClicked(sf::Vector2f posClick)
{
	int button = 0;
	//////////////////////////comprobar el botton Log In logInSprite
	if (posClick.x >= logInSprite.getPosition().x && posClick.x <= logInSprite.getPosition().x + logInSprite.getTextureRect().width &&
	posClick.y >= logInSprite.getPosition().y && posClick.y <= logInSprite.getPosition().y + logInSprite.getTextureRect().height)
	{
	button = 1;
	}
	//////////////////////////comprobar el botton Sign Up
	else if (posClick.x >= signUpSprite.getPosition().x && posClick.x <= signUpSprite.getPosition().x + signUpSprite.getTextureRect().width &&
		posClick.y >= signUpSprite.getPosition().y && posClick.y <= signUpSprite.getPosition().y + signUpSprite.getTextureRect().height)
	{
		button = 2;
	}

	return button;
}

TypeScene FirstChoice::DrawScene()
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

void FirstChoice::DrawSprites()
{
	window.draw(logInSprite);
	window.draw(signUpSprite);
}

void FirstChoice::InputControl(sf::RenderWindow * window)
{

	sf::Event event;
	int buttonClicked = 0;
	sf::Vector2f mousePosition;

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
				std::cout << "Se ha Clickado el botton Log In" << std::endl;
				myTypeScene = TypeScene::GOTO_LOG_IN;
				window->close();
				break;
			case 2:
				std::cout << "Se ha Clickado el botton Sign Up" << std::endl;
				myTypeScene = TypeScene::GOTO_SIGN_UP;
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

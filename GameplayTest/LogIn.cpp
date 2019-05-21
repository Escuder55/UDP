#include "LogIn.h"



LogIn::LogIn()
{
	InitSprites();
}

LogIn::LogIn(int i, sf::UdpSocket* _socket)
{
	socket = _socket;

	InitWindow();
	InitSprites();
	InitText();
	typingPosition = 1;
}


LogIn::~LogIn()
{
	
}

TypeScene LogIn::DrawScene()
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

void LogIn::InitText()
{
	if (!myFont.loadFromFile("res/fonts/courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE USER
	user = "USER";
	userText.setString(user);
	userText.setFont(myFont);
	userText.setCharacterSize(35);
	userText.setFillColor(sf::Color(0, 200, 0));
	userText.setStyle(sf::Text::Bold);
	userText.setPosition(sf::Vector2f((SCREEN_WIDTH/2)-50, 50));
	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	userRect.setSize(sf::Vector2f(300, 50));
	userRect.setFillColor(sf::Color(255, 255, 255, 255));
	userRect.setPosition((SCREEN_WIDTH /2)-150 , 100);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA EL USUARIO
	userAnswer = "";
	userAnswerText.setString(userAnswer);
	userAnswerText.setFont(myFont);
	userAnswerText.setCharacterSize(30);
	userAnswerText.setFillColor(sf::Color(0, 0, 255));
	userAnswerText.setStyle(sf::Text::Bold);
	userAnswerText.setPosition((SCREEN_WIDTH / 2) - 150, 100);


	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE PASSWORD
	password = "PASSWORD";
	passwordText.setString(password);
	passwordText.setFont(myFont);
	passwordText.setCharacterSize(35);
	passwordText.setFillColor(sf::Color(0, 200, 0));
	passwordText.setStyle(sf::Text::Bold);
	passwordText.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - 75, 200));
	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	passwordRect.setSize(sf::Vector2f(300, 50));
	passwordRect.setFillColor(sf::Color(255, 255, 255, 255));
	passwordRect.setPosition((SCREEN_WIDTH / 2) - 150, 250);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA LA CONRASEÑA
	passwordAnswer = "";
	secretPasword = "";
	passwordAnswerText.setString(secretPasword);
	passwordAnswerText.setFont(myFont);
	passwordAnswerText.setCharacterSize(30);
	passwordAnswerText.setFillColor(sf::Color(0, 0, 255));
	passwordAnswerText.setStyle(sf::Text::Bold);
	passwordAnswerText.setPosition((SCREEN_WIDTH / 2) - 150, 250);
}

void LogIn::InitSprites()
{
	/////////////////////////////////////////////////////////////LOGIN BUTTON
	if (!buttonTexture.loadFromFile("res/img/Button_Confirm.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(SCREEN_WIDTH / 2-100 , SCREEN_HEIGHT - 150);
}

void LogIn::DrawText()
{
	window.draw(userText);
	window.draw(userRect);
	///////actualizamos el texto
	userAnswerText.setString(userAnswer);
	window.draw(userAnswerText);


	window.draw(passwordText);
	window.draw(passwordRect);
	///////actualizamos el texto
	passwordAnswerText.setString(secretPasword);
	window.draw(passwordAnswerText); 
	
}

void LogIn::DrawSprites()
{
	window.draw(buttonSprite);
}

bool LogIn::CheckButtonClicked(sf::Vector2f posClick)
{
	bool Clicked = false;
	//////////////////////////comprobar el botton Confirm
	if (posClick.x >= buttonSprite.getPosition().x && posClick.x <= buttonSprite.getPosition().x + buttonSprite.getTextureRect().width &&
		posClick.y >= buttonSprite.getPosition().y && posClick.y <= buttonSprite.getPosition().y + buttonSprite.getTextureRect().height)
	{
		Clicked = true;
	}
	return Clicked;
}

void LogIn::InputControl(sf::RenderWindow * window)
{
	sf::Event event;
	sf::Vector2f mousePosition;
	myTypeScene = TypeScene::LOG_IN;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			CloseWindow();
			break;
		case sf::Event::MouseButtonPressed:
			if (typingPosition > 1)
			{
				mousePosition.x = event.mouseButton.x;
				mousePosition.y = event.mouseButton.y;
				if (CheckButtonClicked(mousePosition))
				{
					sf::Packet pack;
					/////////////////////////////////////////////Cambiar esto
					pack << PROTOCOLO::LOGIN << me.id << me.counterPacket << userAnswer << passwordAnswer;
					sendPacket(pack, IP, PORT);
					me.counterPacket++;

					///// ------------- VAMOS A LA ESCENA MENU ------------- /////					
					window->close();
				}
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
				myTypeScene = TypeScene::EXIT;
			}
			if (event.key.code == sf::Keyboard::Return)
			{
				if (typingPosition == 1)
				{
					typingPosition++;
				}
			}
			break;
		case sf::Event::TextEntered:
			if (typingPosition == 1)
			{
				///////////////////////////////////////////////////////////////////////////GUARDAR LETRAS ESCRITAS
				if (event.text.unicode >= 32 && event.text.unicode <= 126 && userAnswer.length() < 13)
					userAnswer += (char)event.text.unicode;
				///////////////////////////////////////////////////////////////////////////BORRA
				else if (event.text.unicode == 8 && userAnswer.length() > 0)
					userAnswer.erase(userAnswer.length() - 1, userAnswer.length());
			}
			else
			{
				///////////////////////////////////////////////////////////////////////////GUARDAR LETRAS ESCRITAS
				if (event.text.unicode >= 32 && event.text.unicode <= 126 && passwordAnswer.length() < 13)
				{
					passwordAnswer += (char)event.text.unicode;
					secretPasword += "*";
				}
				///////////////////////////////////////////////////////////////////////////BORRA
				else if (event.text.unicode == 8 && passwordAnswer.length() > 0)
				{
					passwordAnswer.erase(passwordAnswer.length() - 1, passwordAnswer.length());
					secretPasword.erase(secretPasword.length() - 1, secretPasword.length());
				}
			}
			break;
		default:
			break;
		}
	}
}

void LogIn::sendPacket(sf::Packet &pack, sf::IpAddress _IP, unsigned short _port)
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

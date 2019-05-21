#include "SignUp.h"
#include "Mensaje.h"

SignUp::SignUp()
{
	InitSprites();
}

SignUp::SignUp(int i, sf::UdpSocket* _socket)
{
	socket = _socket;

	InitWindow();
	InitSprites();
	InitText();
	typingPosition = 1;
}


SignUp::~SignUp()
{
}

void SignUp::InitSprites()
{
	if (!myFont2.loadFromFile("res/fonts/courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}
	/////////////////////////////////////////////////////////////LOGIN BUTTON
	if (!confirmTexture.loadFromFile("res/img/Button_Confirm.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	confirmSprite.setTexture(confirmTexture);
	confirmSprite.setPosition((SCREEN_WIDTH/2)-100, SCREEN_HEIGHT - 100);


	/////////////////////////////////////////////////////////CHARACTERS;

	/////CHARACTER 1
	if (!texturesCharacter1.loadFromFile("res/img/Character1.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters1.setTexture(texturesCharacter1);
	characters1.setPosition((SCREEN_WIDTH/2)+25, 75);

	rectangle1.setSize(sf::Vector2f(50, 80));
	rectangle1.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle1.setPosition(characters1.getPosition());

	one = "1";
	oneText.setString(one);
	oneText.setFont(myFont);
	oneText.setCharacterSize(35);
	oneText.setFillColor(sf::Color(0, 200, 0));
	oneText.setStyle(sf::Text::Bold);
	oneText.setPosition(characters1.getPosition().x+15, characters1.getPosition().y+80);

	/////CHARACTER 2
	if (!texturesCharacter2.loadFromFile("res/img/Character2.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters2.setTexture(texturesCharacter2);
	characters2.setPosition((SCREEN_WIDTH / 2) + 100, 75);

	rectangle2.setSize(sf::Vector2f(50, 80));
	rectangle2.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle2.setPosition(characters2.getPosition().x, characters2.getPosition().y);

	two = "2";
	twoText.setString(two);
	twoText.setFont(myFont);
	twoText.setCharacterSize(35);
	twoText.setFillColor(sf::Color(0, 200, 0));
	twoText.setStyle(sf::Text::Bold);
	twoText.setPosition(characters2.getPosition().x + 15, characters2.getPosition().y + 80);

	/////CHARACTER 3
	if (!texturesCharacter3.loadFromFile("res/img/Character3.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters3.setTexture(texturesCharacter3);
	characters3.setPosition((SCREEN_WIDTH / 2) + 175, 75);

	rectangle3.setSize(sf::Vector2f(50, 80));
	rectangle3.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle3.setPosition(characters3.getPosition().x, characters3.getPosition().y);

	three = "3";
	threeText.setString(three);
	threeText.setFont(myFont);
	threeText.setCharacterSize(35);
	threeText.setFillColor(sf::Color(0, 200, 0));
	threeText.setStyle(sf::Text::Bold);
	threeText.setPosition(characters3.getPosition().x + 15, characters3.getPosition().y + 80);

	/////CHARACTER 4
	if (!texturesCharacter4.loadFromFile("res/img/Character4.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters4.setTexture(texturesCharacter4);
	characters4.setPosition((SCREEN_WIDTH / 2) + 250, 75);

	rectangle4.setSize(sf::Vector2f(50, 80));
	rectangle4.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle4.setPosition(characters4.getPosition().x, characters4.getPosition().y);

	four = "4";
	fourText.setString(four);
	fourText.setFont(myFont);
	fourText.setCharacterSize(35);
	fourText.setFillColor(sf::Color(0, 200, 0));
	fourText.setStyle(sf::Text::Bold);
	fourText.setPosition(characters4.getPosition().x + 15, characters4.getPosition().y + 80);

	/////CHARACTER 5
	if (!texturesCharacter5.loadFromFile("res/img/Character5.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters5.setTexture(texturesCharacter5);
	characters5.setPosition((SCREEN_WIDTH / 2) + 25, 200);

	rectangle5.setSize(sf::Vector2f(50, 80));
	rectangle5.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle5.setPosition(characters5.getPosition());

	five = "5";
	fiveText.setString(five);
	fiveText.setFont(myFont);
	fiveText.setCharacterSize(35);
	fiveText.setFillColor(sf::Color(0, 200, 0));
	fiveText.setStyle(sf::Text::Bold);
	fiveText.setPosition(characters5.getPosition().x + 15, characters5.getPosition().y + 80);

	/////CHARACTER 6
	if (!texturesCharacter6.loadFromFile("res/img/Character6.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters6.setTexture(texturesCharacter6);
	characters6.setPosition((SCREEN_WIDTH / 2) + 100, 200);

	rectangle6.setSize(sf::Vector2f(50, 80));
	rectangle6.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle6.setPosition(characters6.getPosition().x, characters6.getPosition().y);

	six = "6";
	sixText.setString(six);
	sixText.setFont(myFont);
	sixText.setCharacterSize(35);
	sixText.setFillColor(sf::Color(0, 200, 0));
	sixText.setStyle(sf::Text::Bold);
	sixText.setPosition(characters6.getPosition().x + 15, characters6.getPosition().y + 80);

	/////CHARACTER 7
	if (!texturesCharacter7.loadFromFile("res/img/Character7.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters7.setTexture(texturesCharacter7);
	characters7.setPosition((SCREEN_WIDTH / 2) + 175, 200);

	rectangle7.setSize(sf::Vector2f(50, 80));
	rectangle7.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle7.setPosition(characters7.getPosition().x, characters7.getPosition().y);

	seven = "7";
	sevenText.setString(seven);
	sevenText.setFont(myFont);
	sevenText.setCharacterSize(35);
	sevenText.setFillColor(sf::Color(0, 200, 0));
	sevenText.setStyle(sf::Text::Bold);
	sevenText.setPosition(characters7.getPosition().x + 15, characters7.getPosition().y + 80);

	/////CHARACTER 8
	if (!texturesCharacter8.loadFromFile("res/img/Character8.png"))
	{
		std::cout << "Cannot Load the image" << std::endl;
	}
	characters8.setTexture(texturesCharacter8);
	characters8.setPosition((SCREEN_WIDTH / 2) + 250, 200);

	rectangle8.setSize(sf::Vector2f(50, 80));
	rectangle8.setFillColor(sf::Color(0, 0, 250, 255));
	rectangle8.setPosition(characters8.getPosition().x, characters8.getPosition().y);

	eight = "8";
	eightText.setString(eight);
	eightText.setFont(myFont);
	eightText.setCharacterSize(35);
	eightText.setFillColor(sf::Color(0, 200, 0));
	eightText.setStyle(sf::Text::Bold);
	eightText.setPosition(characters8.getPosition().x + 15, characters8.getPosition().y + 80);
}

void SignUp::InitText()
{

	if (!myFont.loadFromFile("res/fonts/courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	//////////////////////////////
	//////////////////////////////ZONA USER
	//////////////////////////////

	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE USER
	user = "USER";
	userText.setString(user);
	userText.setFont(myFont);
	userText.setCharacterSize(35);
	userText.setFillColor(sf::Color(0, 200, 0));
	userText.setStyle(sf::Text::Bold);
	userText.setPosition(sf::Vector2f( 50, 50));
	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	userRect.setSize(sf::Vector2f(300, 50));
	userRect.setFillColor(sf::Color(255, 255, 255, 255));
	userRect.setPosition( 50, 100);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA EL USUARIO
	userAnswer = "";
	userAnswerText.setString(userAnswer);
	userAnswerText.setFont(myFont);
	userAnswerText.setCharacterSize(30);
	userAnswerText.setFillColor(sf::Color(0, 0, 255));
	userAnswerText.setStyle(sf::Text::Bold);
	userAnswerText.setPosition(50, 100);

	//////////////////////////////
	//////////////////////////////ZONA PASSWORD
	//////////////////////////////

	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE PASSWORD
	password = "PASSWORD";
	passwordText.setString(password);
	passwordText.setFont(myFont);
	passwordText.setCharacterSize(35);
	passwordText.setFillColor(sf::Color(0, 200, 0));
	passwordText.setStyle(sf::Text::Bold);
	passwordText.setPosition(sf::Vector2f( 50, 150));
	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	passwordRect.setSize(sf::Vector2f(300, 50));
	passwordRect.setFillColor(sf::Color(255, 255, 255, 255));
	passwordRect.setPosition(50, 200);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA LA CONRASEÑA
	passwordAnswer = "";
	secretPasword = "";
	passwordAnswerText.setString(secretPasword);
	passwordAnswerText.setFont(myFont);
	passwordAnswerText.setCharacterSize(30);
	passwordAnswerText.setFillColor(sf::Color(0, 0, 255));
	passwordAnswerText.setStyle(sf::Text::Bold);
	passwordAnswerText.setPosition(50, 200);

	//////////////////////////////
	//////////////////////////////ZONA REPEAT PASSWORD
	//////////////////////////////

	/////////////////////////////////////////////////////////////////////////////INICIALIZAR EL TEXTO DE REPEAT PASSWORD
	repeatPassword = "REPEAT PASSWORD";
	repeatPasswordText.setString(repeatPassword);
	repeatPasswordText.setFont(myFont);
	repeatPasswordText.setCharacterSize(35);
	repeatPasswordText.setFillColor(sf::Color(0, 200, 0));
	repeatPasswordText.setStyle(sf::Text::Bold);
	repeatPasswordText.setPosition(sf::Vector2f( 50, 250));
	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	repeatPasswordRect.setSize(sf::Vector2f(300, 50));
	repeatPasswordRect.setFillColor(sf::Color(255, 255, 255, 255));
	repeatPasswordRect.setPosition(50, 300);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA LA REPEAT PASSWORD
	repeatPasswordAnswer = "";
	repeatSecretPasword = "";
	repeatPasswordAnswerText.setString(secretPasword);
	repeatPasswordAnswerText.setFont(myFont);
	repeatPasswordAnswerText.setCharacterSize(30);
	repeatPasswordAnswerText.setFillColor(sf::Color(0, 0, 255));
	repeatPasswordAnswerText.setStyle(sf::Text::Bold);
	repeatPasswordAnswerText.setPosition(50, 300);

	//////////////////////////////
	//////////////////////////////ZONA SKIN
	//////////////////////////////

	//////////////////////////////////////////////////////////////////////////////INICIALIZAR RECUADRO DE ESCRITURA
	rectangleSkin.setSize(sf::Vector2f(50, 50));
	rectangleSkin.setFillColor(sf::Color(255, 255, 255, 255));
	rectangleSkin.setPosition((SCREEN_WIDTH / 2) + 125, 350);
	/////////////////////////////////////////////////////////////////////////////INICIALIZAR TEXTO QUE ESCRIBIRA EL USUSARIO PARA EL USUARIO
	skin = "";
	skinText.setString(skin);
	skinText.setFont(myFont);
	skinText.setCharacterSize(30);
	skinText.setFillColor(sf::Color(0, 0, 255));
	skinText.setStyle(sf::Text::Bold);
	skinText.setPosition((SCREEN_WIDTH / 2) + 125, 350);

}

TypeScene SignUp::DrawScene()
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

void SignUp::DrawSprites()
{
	///////CHARACTER 1
	window.draw(rectangle1);
	window.draw(characters1);
	window.draw(oneText);
	///////CHARACTER 2
	window.draw(rectangle2);
	window.draw(characters2);
	window.draw(twoText);
	///////CHARACTER 3
	window.draw(rectangle3);
	window.draw(characters3);
	window.draw(threeText);
	///////CHARACTER 4
	window.draw(rectangle4);
	window.draw(characters4);
	window.draw(fourText);
	///////CHARACTER 5
	window.draw(rectangle5);
	window.draw(characters5);
	window.draw(fiveText);
	///////CHARACTER 6
	window.draw(rectangle6);
	window.draw(characters6);
	window.draw(sixText);
	///////CHARACTER 7
	window.draw(rectangle7);
	window.draw(characters7);
	window.draw(sevenText);
	///////CHARACTER 8
	window.draw(rectangle8);
	window.draw(characters8);
	window.draw(eightText);

	window.draw(confirmSprite);
}

void SignUp::DrawText()
{
	////////////////////////////USER
	window.draw(userText);
	window.draw(userRect);
	///////actualizamos el texto
	userAnswerText.setString(userAnswer);
	window.draw(userAnswerText);

	/////////////////////////////PASSWORD
	window.draw(passwordText);
	window.draw(passwordRect);
	///////actualizamos el texto
	passwordAnswerText.setString(secretPasword);
	window.draw(passwordAnswerText);

	/////////////////////////////REPEAT PASSWORD
	window.draw(repeatPasswordText);
	window.draw(repeatPasswordRect);
	///////actualizamos el texto
	repeatPasswordAnswerText.setString(repeatSecretPasword);
	window.draw(repeatPasswordAnswerText);

	/////////////////////////////SKIN
	window.draw(rectangleSkin);
	skinText.setString(skin);
	window.draw(skinText);
}

bool SignUp::CheckButtonClicked(sf::Vector2f posClick)
{
	bool Clicked = false;
	//////////////////////////comprobar el botton Confirm
	if (posClick.x >= confirmSprite.getPosition().x && posClick.x <= confirmSprite.getPosition().x + confirmSprite.getTextureRect().width &&
		posClick.y >= confirmSprite.getPosition().y && posClick.y <= confirmSprite.getPosition().y + confirmSprite.getTextureRect().height)
	{
		Clicked = true;
	}
	return Clicked;
}

void SignUp::InputControl(sf::RenderWindow * window)
{
	//PAQUETE
	sf::Packet pack;

	sf::Event event;
	sf::Vector2f mousePosition;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			CloseWindow();
			break;
		case sf::Event::MouseButtonPressed:
			if (typingPosition == 4)
			{
				mousePosition.x = event.mouseButton.x;
				mousePosition.y = event.mouseButton.y;
				if ( skin.length() > 0 && CheckButtonClicked(mousePosition))
				{
					
						//ENVIAMOS PAQUETE DE REGISTRO
						pack << PROTOCOLO::REGISTER;
						pack << me.id;
						pack << me.counterPacket;
						pack << userAnswer;
						pack << passwordAnswer;
						pack << repeatPasswordAnswer;
						pack << skin;						
						me.counterPacket++;
						sendPacket(pack,IP,PORT);

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
				else if (typingPosition == 2)
				{
					typingPosition++;
				}
				else if (typingPosition == 3)
				{
					typingPosition++;
				}
				

			}
			break;
		case sf::Event::TextEntered:
			/////////////////////////////////////////// USER
			if (typingPosition == 1)
			{
				///////////////////////////////////////////////////////////////////////////GUARDAR LETRAS ESCRITAS
				if (event.text.unicode >= 32 && event.text.unicode <= 126 && userAnswer.length() < 13)
					userAnswer += (char)event.text.unicode;
				///////////////////////////////////////////////////////////////////////////BORRA
				else if (event.text.unicode == 8 && userAnswer.length() > 0)
					userAnswer.erase(userAnswer.length() - 1, userAnswer.length());
			}
			/////////////////////////////////////////// PASSWORD
			else if(typingPosition == 2)
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
			/////////////////////////////////////////// REPEAT PASSWORD
			else if (typingPosition == 3)
			{
				///////////////////////////////////////////////////////////////////////////GUARDAR LETRAS ESCRITAS
				if (event.text.unicode >= 32 && event.text.unicode <= 126 && repeatPasswordAnswer.length() < 13)
				{
					repeatPasswordAnswer += (char)event.text.unicode;
					repeatSecretPasword += "*";
				}
				///////////////////////////////////////////////////////////////////////////BORRA
				else if (event.text.unicode == 8 && passwordAnswer.length() > 0)
				{
					repeatPasswordAnswer.erase(repeatPasswordAnswer.length() - 1, repeatPasswordAnswer.length());
					repeatSecretPasword.erase(repeatSecretPasword.length() - 1, repeatSecretPasword.length());
				}
			}
			/////////////////////////////////////////// SKIN
			else if (typingPosition == 4)
			{
				///////////////////////////////////////////////////////////////////////////GUARDAR LETRAS ESCRITAS
				if (event.text.unicode >= 32 && event.text.unicode <= 126 && skin.length() < 1)
				{
					skin += (char)event.text.unicode;
				}
				///////////////////////////////////////////////////////////////////////////BORRA
				else if (event.text.unicode == 8 && skin.length() > 0)
				{
					skin.erase(skin.length() - 1, skin.length());
				}
			}
			break;
		default:
			break;
		}
	}

}

void SignUp::sendPacket(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port)
{
	startTime = clock();
	while (!finishSending)
	{
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		if (timeInSeconds>=0.5)
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

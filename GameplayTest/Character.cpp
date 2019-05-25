#include "Character.h"



Character::Character()
{
}

Character::Character(CharacterType _myCharacter, sf::UdpSocket *sock)
{
	//Nos guardamos el socket
	socket = sock;
	//
	idAccum = 0;
	startTime = clock();
	startTime2 = clock();
	// para acumulados
	accumMovementForPacket.push_back({characterPosition.x, characterPosition.y});

	moving = Direcciones::NONE;
	shooting = Direcciones::NONE;
	///////////////////////////////////////////////////EN FUNCIÓN DEL CHARACTER ESCOGIDO INICIALIZAREMOS
	///////////////////////////////////////////////////LA POSICION DEL RECTANGLE DEL SPRITE PARA COGER EL ASPECTO ESCOGIDO
	switch (_myCharacter)
	{
	case CharacterType::ONE:
			spritePosition.x = 0;
			spritePosition.y = 0;
		break;
	case CharacterType::TWO:
		spritePosition.x = 156;
		spritePosition.y = 0;
		break;
	case CharacterType::THREE:
		spritePosition.x = 312;
		spritePosition.y = 0;
		break;
	case CharacterType::FOUR:
		spritePosition.x = 468;
		spritePosition.y = 0;
		break;
	case CharacterType::FIVE:
		spritePosition.x = 0;
		spritePosition.y = 288;
		break;
	case CharacterType::SIX:
		spritePosition.x = 156;
		spritePosition.y = 288;
		break;
	case CharacterType::SEVEN:
		spritePosition.x = 312;
		spritePosition.y = 288;
		break;
	case CharacterType::EIGHT:
		spritePosition.x = 468;
		spritePosition.y = 288;
		break;
	default:
		break;
	}

	/////////////////////////inicializamos la posición del personaje, 
	/////////////////////////esta en un futuro tendra que ser en función de que puerta entramos 
	characterPosition.x = SCREEN_WIDTH / 2;
	characterPosition.y = SCREEN_HEIGHT / 2;

	////////////inicializamos la velocidad del personaje
	speed = 10;
	InitSprites();
}


Character::~Character()
{
}

void Character::InitSprites()
{
	/////////////////////////////////////////////////////////////CARGAMOS LA TEXTURA CON TODAS LAS SKINS
	if (!cTexture.loadFromFile("res/img/CharactersSprites.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	characterSprite.setTexture(cTexture);
	myRect = { static_cast<int>(spritePosition.x), static_cast<int>(spritePosition.y), SPRITE_CHARACTER_WIDTH,SPRITE_CHARACTER_HEIGHT };
	characterSprite.setTextureRect(myRect);
	characterSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
}

void Character::DrawCharacter(sf::RenderWindow * window)
{
	endTime = clock();
	clockTicksTaken = endTime - startTime;
	timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
	clockTicksTaken = endTime - startTime2;
	timeInSeconds2 = clockTicksTaken / (double)CLOCKS_PER_SEC;;

	timeCounter++;
	
	if (timeCounter > 350)
	{
		timeCounter = 0;
		animationCounterX++;

		if (animationCounterX > 2)
		{
			animationCounterX = 0;
			
		}		
		/////////////////////////// UNA VEZ ACTUALIZADO EL ANIMATION COUNTER QUE SIRVE PARA SABER QUE IMAGEN COGER DE LA ANIMACIÓN
		/////////////////////////// SE LA APLICAMOS AL RECTANGLE DEL SPRITE DE NUESTRO PERSONAJE
		myRect = {	static_cast<int>(spritePosition.x) + (animationCounterX*SPRITE_CHARACTER_WIDTH) , 
					static_cast<int>(spritePosition.y) + (animationCounterY*SPRITE_CHARACTER_HEIGHT),
					SPRITE_CHARACTER_WIDTH, SPRITE_CHARACTER_HEIGHT };
		characterSprite.setTextureRect(myRect);
	}

	//Envio Acumulados////////////////////////////////////////////////
	if (timeInSeconds2 > 0.2)
	{
		startTime2 = clock();
		accumMovementForPacket.push_back({ characterPosition.x, characterPosition.y });
	}
	//Guardamos el envio del packeteAcumulado.
	if (accumMovementForPacket.size() == 5)
	{
		movementPacket.clear();

		movementPacket << PROTOCOLO::MOVEMENT;
		auxMensaje.protocolo = PROTOCOLO::MOVEMENT;

		movementPacket << idAccum;
		auxMensaje.id = idAccum;

		idAccum++;
		//rellenamos el packet para enviarlo con los movimientos acumulados
		for (int i = 0; i < accumMovementForPacket.size(); i++)
		{
			movementPacket << accumMovementForPacket[i].posX;
			movementPacket << accumMovementForPacket[i].posY;

			//std::cout << "POSX :" << accumMovementForPacket[i].posX << " POSY :" << accumMovementForPacket[i].posY << std::endl;
		}
		//Rellenamos lista acumulados
		auxMensaje.pack = movementPacket;
		accumMove.push_back(auxMensaje);
		accumMovementForPacket.clear();
		sf::Socket::Status status = socket->send(movementPacket,IP_CLASE,PORT);
		if (status != sf::Socket::Done)
		{
			std::cout << "No se ha podido enviar el mensaje de movimiento" << std::endl;
		}
		else
		{
			//std::cout << "Se ha enviado el mensaje de movimiento" << std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////
	DrawBullets(window);
	window->draw(characterSprite);

}

void Character::DrawBullets(sf::RenderWindow * window)
{
	if (myBullets.size() > 0)
	{
		for (int i = 0; i < myBullets.size(); i++)
		{

			myBullets[i]->DrawBullet(window);
		}
	}

}

void Character::UpdateCharacterPosition(sf::Keyboard::Key _keyPressed, bool _pressed)
{
	bool enviarMove = false;
	bool enviarDisparo = false;
	moving = NONE;
	shooting = NONE;

	//////////////////////////////////////MOVIMIENTO
	if (_pressed)
	{
		if (_keyPressed == sf::Keyboard::S)
		{
			moving = Direcciones::DOWN;
		}
		else if (_keyPressed == sf::Keyboard::A)
		{
			moving = Direcciones::LEFT;
		}
		else if (_keyPressed == sf::Keyboard::D)
		{
			moving = Direcciones::RIGHT;
		}
		else if (_keyPressed == sf::Keyboard::W)
		{
			moving = Direcciones::UP;
		}
		///////////////////////////////////////////DISPARO

			//////////////UP
		else if (_keyPressed == sf::Keyboard::Up)
		{
			shooting = Direcciones::UP;
		}

		/////////////RIGHT
		else if (_keyPressed == sf::Keyboard::Right)
		{			
			shooting = Direcciones::RIGHT;
		}

		/////////////DOWN
		else if (_keyPressed == sf::Keyboard::Down)
		{			
			shooting = Direcciones::DOWN;
		}

		/////////////LEFT
		else if (_keyPressed == sf::Keyboard::Left)
		{
			shooting = Direcciones::LEFT;
		}
	}
	else if(!_keyPressed)
	{
		////////////////si dejamos de presionar algunas de las teclas de moviento moving pasa a NONE
		if (_keyPressed == sf::Keyboard::W || _keyPressed == sf::Keyboard::A ||
			_keyPressed == sf::Keyboard::S || _keyPressed == sf::Keyboard::D)
		{
			moving = Direcciones::NONE;
		}
		if (_keyPressed == sf::Keyboard::Up || _keyPressed == sf::Keyboard::Right ||
			_keyPressed == sf::Keyboard::Down || _keyPressed == sf::Keyboard::Left)
		{
			shooting = Direcciones::NONE;
		}
	}
	//////////////////////////////comprobamos el movimiento
	switch (moving)
	{
	case NONE:
		
		break;
	case UP:
			animationCounterY = 3;
			characterPosition.y -= speed;
			characterSprite.setPosition(characterPosition);
			enviarMove = true;
		break;

	case RIGHT:
			animationCounterY = 2;
			characterPosition.x += speed;
			characterSprite.setPosition(characterPosition);
			enviarMove = true;
		break;

	case DOWN:
			animationCounterY = 0;
			characterPosition.y += speed;
			characterSprite.setPosition(characterPosition);
			enviarMove = true;
		break;

	case LEFT:
			animationCounterY = 1;
			characterPosition.x -= speed;
			characterSprite.setPosition(characterPosition);
			enviarMove = true;
		break;

	default:
		break;
	}
	
	if (hoverRightDoor())
	{
		std::cout << "Me piro a la sala 2 -----------------------" << std::endl;;
	}
	if (hoverDownDoor())
	{
		std::cout << "Me piro a la sala 3 bro-----------------------" << std::endl;;
	}

	///////////////////////////////////////////DISPARO

	///////////////////////comprobamos los disparos
	switch (shooting)
	{
	case NONE:
		break;

	case UP:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::UP);
			myBullets.push_back(auxBullet);
			enviarDisparo = true;
		break;

	case RIGHT:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::RIGHT);
			myBullets.push_back(auxBullet);
			enviarDisparo = true;
		break;

	case DOWN:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::DOWN);
			myBullets.push_back(auxBullet);
			enviarDisparo = true;
		break;

	case LEFT:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::LEFT);
			myBullets.push_back(auxBullet);
			enviarDisparo = true;
		break;

	default:
		break;
	}
	

}

void Character::cleanAccumMovement(int idConfirmed)
{
	std::cout << "ID packete :" << idConfirmed << std::endl;
	
	std::list<Mensaje>::iterator it = accumMove.begin();
	while (it != accumMove.end()) {
		// Remove elements while iterating
		if (it->id <= idConfirmed) {
			std::cout << "Se borra el que tiene paqueteID :" << it->id << std::endl;
			it = accumMove.erase(it);
		}
		else
			it++;
	}
}


bool Character::hoverRightDoor()
{
	if ((characterSprite.getPosition().x + characterSprite.getTextureRect().width) > DOOR_RIGHT_POS_X)
	{		
		if ((characterSprite.getPosition().y > (DOOR_RIGHT_POS_Y - 45)) && (characterSprite.getPosition().y < (DOOR_RIGHT_POS_Y)))
		{
			return true;
		}
	}
	return false;
}

bool Character::hoverDownDoor()
{
	if ((characterSprite.getPosition().x < DOOR_DOWN_POS_X + 40) && (characterSprite.getPosition().x > DOOR_DOWN_POS_X - 35))
	{
		if (((characterSprite.getPosition().y + characterSprite.getTextureRect().height) > DOOR_DOWN_POS_Y))
		{
			return true;
		}
	}
	return false;
}

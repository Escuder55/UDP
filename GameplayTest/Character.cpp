#include "Character.h"



Character::Character()
{
}

Character::Character(CharacterType _myCharacter)
{
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
		break;

	case RIGHT:
			animationCounterY = 2;
			characterPosition.x += speed;
			characterSprite.setPosition(characterPosition);
		break;

	case DOWN:
			animationCounterY = 0;
			characterPosition.y += speed;
			characterSprite.setPosition(characterPosition);
		break;

	case LEFT:
			animationCounterY = 1;
			characterPosition.x -= speed;
			characterSprite.setPosition(characterPosition);
		break;

	default:
		break;
	}

	///////////////////////////////////////////DISPARO

	///////////////////////comprobamos los disparos
	//////////////////////////////comprobamos el movimiento
	switch (shooting)
	{
	case NONE:
		break;

	case UP:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::UP);
			myBullets.push_back(auxBullet);
		break;

	case RIGHT:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::RIGHT);
			myBullets.push_back(auxBullet);
		break;

	case DOWN:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::DOWN);
			myBullets.push_back(auxBullet);
		break;

	case LEFT:
			auxBullet = new Bullet(characterSprite.getPosition(), Direcciones::LEFT);
			myBullets.push_back(auxBullet);
		break;

	default:
		break;
	}
	
}
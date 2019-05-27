#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(sf::Vector2f _position, Direcciones _currentDirection, int _ID, int _IDSala)
{
	ID = _ID;
	IDSala = _IDSala;
	////////////////////en funcion de la direccion en la que disparemos haremso spawn del proyectil en una posicion determinada
	if (_currentDirection == Direcciones::RIGHT)
	{
		bulletPosition.x = _position.x + SPRITE_CHARACTER_WIDTH;
		bulletPosition.y = _position.y + (SPRITE_CHARACTER_HEIGHT / 2);
	}
	else if (_currentDirection == Direcciones::DOWN)
	{
		bulletPosition.x = _position.x + (SPRITE_CHARACTER_WIDTH / 2) - 10;
		bulletPosition.y = _position.y + SPRITE_CHARACTER_HEIGHT;
	}
	else if (_currentDirection == Direcciones::LEFT)
	{
		bulletPosition.x = _position.x - 30;
		bulletPosition.y = _position.y + (SPRITE_CHARACTER_HEIGHT / 2) - 10;
	}
	else if (_currentDirection == Direcciones::UP)
	{
		bulletPosition.x = _position.x + (SPRITE_CHARACTER_WIDTH / 2);
		bulletPosition.y = _position.y - 30;
	}

	/////////////////////////////////////////////////////////////CARGAMOS LA TEXTURA DE LA BALAS
	if (!myTexture.loadFromFile("res/img/Fire.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	bulletSprite.setTexture(myTexture);	
	bulletSprite.setPosition(bulletPosition);
	bulletSprite.setScale(0.07f, 0.07f);
	myDirection = _currentDirection;
}


Bullet::~Bullet()
{
}

void Bullet::DrawBullet(sf::RenderWindow * window)
{
	UpdateBullet();

	window->draw(bulletSprite);
}

void Bullet::UpdateBullet()
{
	switch (myDirection)
	{
	case Direcciones::UP:
			bulletPosition.y -= bulletSpeed;
			bulletSprite.setPosition(bulletPosition);
		break;
	case Direcciones::RIGHT:
		bulletPosition.x += bulletSpeed;
		bulletSprite.setPosition(bulletPosition);
		break;
	case Direcciones::DOWN:
		bulletPosition.y += bulletSpeed;
		bulletSprite.setPosition(bulletPosition);
		break;
	case Direcciones::LEFT:
		bulletPosition.x -= bulletSpeed;
		bulletSprite.setPosition(bulletPosition);
		break;
	default:
		break;
	}
}

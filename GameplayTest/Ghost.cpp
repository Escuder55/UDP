#include "Ghost.h"



Ghost::Ghost()
{
}

Ghost::Ghost(float _posX, float _posY, int _IDSala, int _ID)
{
	ID = _ID;
	posX = _posX;
	posY = _posY;
	idSala = _IDSala;
	isAlive = true;
	InitSprites();
}

Ghost::~Ghost()
{
}

void Ghost::UpdatePosition(float _posX, float _posY)
{
	posX = _posX;
	posY = _posY;
	ghostSprite.setPosition(posX, posY);
}

void Ghost::DrawGhost(sf::RenderWindow * window)
{
	if (isAlive)
	{
		window->draw(ghostSprite);
	}
}

void Ghost::InitSprites()
{
	if (!ghostTexture.loadFromFile("res/img/Enemy1.png"))
	{
		std::cout << "Cannot Load the image UP DOOR" << std::endl;
	}
	ghostSprite.setTexture(ghostTexture);
	ghostSprite.setPosition(posX, posY);
	ghostSprite.setScale(0.25f, 0.25f);
}

void Ghost::KillGhost()
{
	isAlive = false;
}
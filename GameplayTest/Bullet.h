#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"

class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f _position, Direcciones _currentDirection,int _ID, int _IDSala);
	~Bullet();

	void DrawBullet(sf::RenderWindow * window);
	void UpdateBullet();
	int ID;
	int IDSala;

private:

	Direcciones myDirection;
	sf::Vector2f bulletPosition;
	float bulletSpeed = 0.2;

	sf::Texture myTexture;
	sf::Sprite bulletSprite;
};


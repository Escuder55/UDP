#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Bullet.h"

class Character
{	

public:
	
	Character();
	Character(CharacterType _myCharacter);
	~Character();
	void InitSprites();
	void DrawCharacter(sf::RenderWindow * window);
	void DrawBullets(sf::RenderWindow * window);
	void UpdateCharacterPosition(sf::Keyboard::Key _keyPressed, bool _pressed);

private:
	sf::Texture cTexture;
	sf::IntRect myRect;
	sf::Sprite characterSprite;
	sf::Vector2f spritePosition;

	sf::Vector2f characterPosition;

	int animationCounterX = 0,
		animationCounterY = 3,
		timeCounter = 0;
	float speed;

	Direcciones moving;
	Direcciones shooting;

	Bullet* auxBullet;
	std::vector<Bullet*> myBullets;
};


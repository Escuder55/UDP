#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
class Ghost
{
public:
	Ghost();
	Ghost(float _posX, float _posY, int _IDSala, int _ID);
	~Ghost();

	void UpdatePosition(float _posX, float _posY);

	void DrawGhost(sf::RenderWindow * window);
	void InitSprites();
	void KillGhost();

	sf::Texture ghostTexture;
	sf::Sprite ghostSprite;

	int ID;
	int idSala;
	float posX;
	float posY;
	bool isAlive;
};


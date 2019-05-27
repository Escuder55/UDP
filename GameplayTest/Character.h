#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Bullet.h"
#include <SFML/Network.hpp>
#include "Mensaje.h"
#include <list>
struct movementPlayer 
{
	float posX;
	float posY;
};

class Character
{	

public:
	
	Character();
	Character(CharacterType _myCharacter, sf::UdpSocket *sock, int _ID, int _IDSala);
	~Character();
	void InitSprites();
	void DrawCharacter(sf::RenderWindow * window);
	void DrawBullets(sf::RenderWindow * window);
	void UpdateCharacterPosition(sf::Keyboard::Key _keyPressed, bool _pressed);
	void cleanAccumMovement(int idConfirmed);

	bool changeRoomToRight = false;
	bool changeRoomToLeft = false;
	bool changeRoomToDown = false;
	bool changeRoomToUp = false;

	//CAMBIAMOS POSICION DEL CARACTER
	void CharacterChangeRoom(float posX, float posY);

	bool hoverRightDoor(float x, float y);
	bool hoverDownDoor(float x, float y);
	bool hoverLeftDoor(float x, float y);
	bool hoverUpDoor(float x, float y);
	//BLOCK paredes externas
	bool collisionLeftAll();
	bool collisionDownAll();
	bool collisionRightAll();
	bool collisionUpAll();

	void SendPacket(Direcciones _Direction);

	sf::Vector2f characterPosition;

	int ID;
	int IDSala;

private:
	sf::Texture cTexture;
	sf::IntRect myRect;
	sf::Sprite characterSprite;
	sf::Vector2f spritePosition;

	std::list<Mensaje> accumMove;

	//SALA ACTUAL
	int salaActual;
	
	//Para acumulados
	int idAccum;
	Mensaje auxMensaje;
	std::vector<movementPlayer> accumMovementForPacket;

	//TIMER
	clock_t startTime;
	clock_t startTime2;
	clock_t endTime;
	clock_t clockTicksTaken;
	double timeInSeconds;
	double timeInSeconds2;

	//Network Variable
	sf::UdpSocket *socket;
	sf::Packet movementPacket;
	sf::Packet ShotPacket;
	

	int animationCounterX = 0,
		animationCounterY = 3,
		timeCounter = 0;
	float speed;

	Direcciones moving;
	Direcciones shooting;

	Bullet* auxBullet;
	std::vector<Bullet*> myBullets;

};


#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Constants.h"
#include "PlayerProxy.h"
#include "Ghost.h"
#include "Bullet.h"

class Scene
{
public:
	Scene();
	~Scene();
	void InitWindow();
	void CloseWindow();
	virtual TypeScene DrawScene();
	PlayerProxy me;
	sf::RenderWindow window;

	TypeScene myTypeScene;
	bool finishSending;

	//TIMER
	clock_t startTime;
	clock_t endTime;
	clock_t clockTicksTaken;
	double timeInSeconds;
	//TIMERLERP
	//TIMER
	clock_t startTimeLerp;
	clock_t endTimeLerp;
	clock_t clockTicksTakenLerp;
	double timeInSecondsLerp;

	//PARTNER
	float posPartnerX;
	float posPartnerY;
	sf::Texture partnerTexture;
	sf::Sprite partner;
	int partnerSala;
	int mySala;
	void UpdatePartnerPosition(float _posX, float _posY);
	int currentBackground;
	int partnerID;
	int partnerLive = 1;

	//INTERPOLATION
	void lerp(float Xinicial, float Xfinal, float Yinicial, float Yfinal, float deltaTime, int StartMovement);
	void SetPArtnerId(int _ID);

	// ENEMIGOS
	std::vector<Ghost*> enemies;

	//HUD
	void InitText();
	sf::Font myFont;
	sf::Text PartnerText;
	std::string HUDText;

	////////////------------------ Balas PArtner **************/////////////////
	Bullet* auxBullet;
	std::vector<Bullet*> partnerBullets;


protected:
	virtual void InputControl(sf::RenderWindow* window);
	virtual void sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port);
	virtual void UpdateHUD(int _live, int _ID_Sala);
	virtual void AddNewBullet(float _posX, float _posY, Direcciones _Direction);
};


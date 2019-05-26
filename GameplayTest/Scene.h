#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Constants.h"
#include "PlayerProxy.h"
#include "Ghost.h"

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

	//INTERPOLATION
	void lerp(float Xinicial, float Xfinal, float Yinicial, float Yfinal, float deltaTime, int StartMovement);

	// ENEMIGOS
	std::vector<Ghost*> enemies;
protected:
	virtual void InputControl(sf::RenderWindow* window);
	virtual void sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port);
};


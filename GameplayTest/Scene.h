#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Constants.h"
#include "PlayerProxy.h"


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

protected:
	virtual void InputControl(sf::RenderWindow* window);
	virtual void sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port);
};


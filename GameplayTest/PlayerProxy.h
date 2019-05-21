#pragma once
#include "Mensaje.h"
#include <stack>
#include <SFML/Network.hpp>

class PlayerProxy
{
public:

	//ATTRIBUTES
	sf::IpAddress IP_Adress;
	unsigned short port;
	int id;
	std::string userName;
	int skin;
	int counterPacket;
	std::stack<Mensaje> critic_Msg;
	float posX;
	float posY;
	
	PlayerProxy();
	~PlayerProxy();
};


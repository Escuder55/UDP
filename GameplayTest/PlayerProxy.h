#pragma once
#include "Mensaje.h"
#include <stack>
#include <SFML/Network.hpp>
#include <map>

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
	std::multimap<PROTOCOLO, Mensaje> Critic_Message;
	std::multimap<PROTOCOLO, Mensaje> Regular_Message;
	float posX;
	float posY;
	
	PlayerProxy();
	~PlayerProxy();
};


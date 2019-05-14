#pragma once
#include <SFML/Network.hpp>

class PlayerProxy
{
public:

	//ATTRIBUTES
	sf::IpAddress IP_Adress;
	unsigned short port;
	int id;

	PlayerProxy();
	~PlayerProxy();
};


#pragma once
#include <SFML/Network.hpp>
#include "Constants.h"

class Mensaje
{
public:

	//ATTRIBUTES
	int id;
	sf::Packet pack;

	Mensaje();
	Mensaje(int _id, sf::Packet &_pack);
	~Mensaje();
};


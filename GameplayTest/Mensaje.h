#pragma once
#include <SFML/Network.hpp>
#include "Constants.h"

class Mensaje
{
public:

	//ATTRIBUTES
	int id;
	PROTOCOLO protocol;
	sf::Packet pack;

	Mensaje();
	~Mensaje();
};


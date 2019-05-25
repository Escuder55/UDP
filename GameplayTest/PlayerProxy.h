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
	int id_cuenta;
	std::string userName;
	std::string password;
	int skin;
	int counterPacket;
	std::multimap<PROTOCOLO, Mensaje> Critic_Message;
	std::multimap<PROTOCOLO, Mensaje> Regular_Message;
	float posX;
	float posY;
	int NumEnemigos;
	int idPartidaActual;

	PlayerProxy();
	~PlayerProxy();
};


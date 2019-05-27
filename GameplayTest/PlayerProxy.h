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
	int id_sesion;
	int id_partida;
	int counterPing;
	float startTime=0;
	float disconectMesage = 0;
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
	int idSalaActual = 0;
	bool desconectado = false;
	PlayerProxy();
	~PlayerProxy();
};


#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <list>

#define MAX_MENSAJES 30
#define PORT 50000

////////////////////////////////////JUGADORES
struct players
{
	sf::IpAddress IP_Adress;
	unsigned int port;
	int id;
	int posX;
	int posY;
};

std::vector<players> playersConnecteds;


void main()
{
	sf::UdpSocket socket;
	sf::Socket::Status status;

	status = socket.bind(PORT);
	if(status != sf::Socket::Done)
	{
		std::cout << "no se puede hacer bind bien con el puerto 52000" << std::endl;
	}
	int numPlayers = 0;
	////////////////////////////////varibles protocolo
	std::string protocolo;
	std::string name;
	sf::Packet pack;
	sf::IpAddress adress;
	unsigned short port;

	while (numPlayers < 3)
	{
		status = socket.receive(pack, adress, port);
		if (status == sf::Socket::Done)
		{
			
			pack >> protocolo;
			if (protocolo == "HELLO")
			{
				numPlayers++;
				playersConnecteds.push_back({ adress, port ,numPlayers, numPlayers, numPlayers});

				pack >> name;

				std::cout << "Welcome To " << name << std::endl;

				pack.clear();

				protocolo = "WELCOME";
				int id = numPlayers;

				pack << protocolo << id << numPlayers << numPlayers;				
				if (numPlayers > 1)
				{
					for (int i = 0; i < playersConnecteds.size()-1; i++)
					{
						std::cout << "entras?" << std::endl;
						pack << playersConnecteds[i].id << playersConnecteds[i].posX << playersConnecteds[i].posY;
					}

				}
				socket.send(pack,  playersConnecteds[numPlayers-1].IP_Adress, playersConnecteds[numPlayers-1].port);
			}
			
		}
	}
	while (true)
	{
		
	}
}
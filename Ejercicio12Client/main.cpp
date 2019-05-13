#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

#define MAX_MENSAJES 30
#define IP "192.168.56.1"
#define IP_CLASE "10.40.0.78"
#define PORT 50000

sf::RenderWindow window;


std::vector<sf::CircleShape> circles;
///////////////////////////////para la conexion
sf::Socket::Status status;
sf::Packet pack;
sf::UdpSocket socket;

////////////////////////////RECIEVE
void recieveThread()
{
	sf::Packet pack2;
	sf::IpAddress adressServer = IP;
	unsigned short port = PORT;
	int posX, posY;

	socket.receive(pack2, adressServer, port);

	std::string proto;

	pack2 >> proto;

	if (proto == "NEWPLAYER")
	{
		pack2 >> posX;
		pack2 >> posY;
		std::cout << "Se ha conectado un nuevo PLAYER. Posiciones posX = " << posX << " posY = " << posY << ". " << std::endl; 

		sf::CircleShape circle;
		circle.setFillColor(sf::Color::Green);
		circle.setRadius(20.0f);
		circle.setPosition((posX - 1) * 20, (posY - 1) * 20);
		circles.push_back(circle);
	}

}


void main()
{	
	

	sf::IpAddress adreesServer = IP;
	unsigned short port = PORT;

	////////////////////////////////para protocolo
	std::string protocolo= "HELLO";
	std::string name;

	std::cout << "Write your name" << std::endl;
	std::cin >> name;

	pack << protocolo << name;

	///////////////////////////////////////////////////conectamos con el server
	status = socket.send(pack, adreesServer, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "No se ha podido enviar el mensaje" << std::endl;
	}

	status = socket.receive(pack, adreesServer, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "No se ha podido enviar el mensaje" << std::endl;
	}
	int idPlayer;

	int posX, posY;
	pack >> protocolo >> idPlayer >> posX >> posY;
	

	if (protocolo == "WELCOME")
	{
		std::cout << "My player ID es " << idPlayer << ", my pos X = "<< posX << "  and my pos Y = " << posY << ". "<<std::endl;
		window.create(sf::VideoMode(400, 400), "Ejercicio 12");
	}
	pack.clear();

	std::thread t(&recieveThread);
	t.detach();

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(20.0f);
	circle.setPosition((posX - 1) * 20, (posY - 1) * 20);
	circles.push_back(circle);

	int idOther;

	if (idPlayer > 1)
	{
		for (int i = 0; i < idPlayer - 1; i++)
		{
			pack >> idOther;
			pack >> posX;
			pack >> posY;

			std::cout << "El Player con id = " << idOther << " y posiciones posX = " << posX << " posY = " << posY << ". " << std::endl;

			sf::CircleShape circle;
			circle.setFillColor(sf::Color::Green);
			circle.setRadius(20.0f);
			circle.setPosition((posX - 1) * 20, (posY - 1) * 20);
			circles.push_back(circle);
		}
	}
	

	while (window.isOpen())
	{

		
		for (int i = 0; i < circles.size(); i++)
		{
			window.draw(circles[i]);
		}
		window.display();
		window.clear();
	}
	
}

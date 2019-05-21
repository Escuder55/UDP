#pragma once
#include "Scene.h"
class Maps :
	public Scene
{
public:
	Maps();
	Maps(int i, sf::UdpSocket* _socket);
	~Maps();

	void InitSprites();
	void DrawSprites();
	TypeScene DrawScene();
	int CheckButtonClicked(sf::Vector2f posClick);
	void InputControl(sf::RenderWindow* window);
	void sendPacket(sf::Packet &pack, sf::IpAddress _IP, unsigned short _port);
private:
	sf::Texture map1Texture;
	sf::Sprite  map1Sprite;

	sf::Texture map2Texture;
	sf::Sprite  map2Sprite;

	sf::Texture map3Texture;
	sf::Sprite  map3Sprite;

	sf::Texture backTexture;
	sf::Sprite  backSprite;

	TypeScene myTypeScene;

	//////////////////////////puntero a socket;
	sf::UdpSocket *socket;

};


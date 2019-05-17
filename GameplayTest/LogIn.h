#pragma once
#include "Scene.h"
class LogIn :
	public Scene
{
public:
	LogIn();
	LogIn(int i, sf::UdpSocket* _socket);
	~LogIn();

	TypeScene DrawScene();
	void InitText();
	void InitSprites();
	void DrawText();
	void DrawSprites();
	bool CheckButtonClicked(sf::Vector2f posClick);
	void InputControl(sf::RenderWindow* window);
	void sendPacket(sf::Packet &pack, sf::IpAddress _IP, unsigned short _port);
private:
	//////////////////////////puntero a socket;
	sf::UdpSocket *socket;


	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	sf::Font myFont;

	sf::Text userText;
	std::string user;
	sf::Text userAnswerText;
	std::string userAnswer;
	sf::RectangleShape userRect;

	sf::Text passwordText;
	sf::Text passwordAnswerText;
	std::string password;
	std::string passwordAnswer;
	std::string secretPasword;
	sf::RectangleShape passwordRect;

	int typingPosition;
	
	TypeScene myTypeScene;

	bool confirmClicked;

};


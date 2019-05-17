#pragma once
#include "Scene.h"

class SignUp :
	public Scene
{
public:
	SignUp();
	SignUp(int i, sf::UdpSocket* _socket);
	~SignUp();
	void InitSprites();
	void InitText();
	TypeScene DrawScene();
	void DrawSprites();
	void DrawText();
	bool CheckButtonClicked(sf::Vector2f posClick);
	void InputControl(sf::RenderWindow* window);
	void sendPacket(sf::Packet &pack, sf::IpAddress _IP, unsigned short _port);

private:
	//////////////////////////puntero a socket;
	sf::UdpSocket *socket;

	sf::Font myFont;

	///////////////////USER
	sf::Text userText;
	std::string user;
	sf::Text userAnswerText;
	std::string userAnswer;
	sf::RectangleShape userRect;

	///////////////////PASSWORD
	sf::Text passwordText;
	sf::Text passwordAnswerText;
	std::string password;
	std::string passwordAnswer;
	std::string secretPasword;
	sf::RectangleShape passwordRect;

	///////////////////REPEAT PASSWORD
	sf::Text repeatPasswordText;
	sf::Text repeatPasswordAnswerText;
	std::string repeatPassword;
	std::string repeatPasswordAnswer;
	std::string repeatSecretPasword;
	sf::RectangleShape repeatPasswordRect;

	///////////////////NUMERO DE SKIN
	sf::RectangleShape rectangleSkin;
	std::string skin;
	sf::Text skinText;

	/////////////////// BOTTON CONFRIM
	sf::Texture confirmTexture;
	sf::Sprite confirmSprite;

	//////////////////////CHARACTERS
		sf::Font myFont2;
		////CHARACTER 1
		sf::Texture texturesCharacter1;
		sf::Sprite characters1;
		sf::RectangleShape rectangle1;
		std::string one;
		sf::Text oneText;
		////CHARACTER 2
		sf::Texture texturesCharacter2;
		sf::Sprite characters2;
		sf::RectangleShape rectangle2;
		std::string two;
		sf::Text twoText;
		////CHARACTER 3
		sf::Texture texturesCharacter3;
		sf::Sprite characters3;
		sf::RectangleShape rectangle3;
		std::string three;
		sf::Text threeText;
		////CHARACTER 4
		sf::Texture texturesCharacter4;
		sf::Sprite characters4;
		sf::RectangleShape rectangle4;
		std::string four;
		sf::Text fourText;
		////CHARACTER 5
		sf::Texture texturesCharacter5;
		sf::Sprite characters5;
		sf::RectangleShape rectangle5;
		std::string five;
		sf::Text fiveText;
		////CHARACTER 6
		sf::Texture texturesCharacter6;
		sf::Sprite characters6;
		sf::RectangleShape rectangle6;
		std::string six;
		sf::Text sixText;
		////CHARACTER 7
		sf::Texture texturesCharacter7;
		sf::Sprite characters7;
		sf::RectangleShape rectangle7;
		std::string seven;
		sf::Text sevenText;
		////CHARACTER 8
		sf::Texture texturesCharacter8;
		sf::Sprite characters8;
		sf::RectangleShape rectangle8;
		std::string eight;
		sf::Text eightText;

	int typingPosition;

	TypeScene myTypeScene;
};


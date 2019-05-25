#pragma once
#include "Scene.h"
#include"Character.h"

class Game :
	public Scene
{
public:
	Game();
	Game(CharacterType myCharacterType, float _posX, float _posY, sf::UdpSocket *sock, int skin);
	~Game();
	void InitSprites();
	TypeScene DrawScene();
	void InputControl(sf::RenderWindow* window);
	void DrawSprites();
	bool doorsOpen;
	int	spriteWidth = 291,
		spriteHeight = 477;
	int animationCounterX = 0,
		animationCounterY = 0,
		timeCounter = 0;
	sf::IntRect myRect;
	sf::Packet GamePack;
	int partnerSkin;
	Character* myCharacter;


private:
	sf::Texture  bgTexture[4];
	sf::Texture  doorTexture[4];
	sf::Sprite background[3];
	sf::Sprite doors[4];
	sf::UdpSocket *socket;


	TypeScene myTypeScene;
};


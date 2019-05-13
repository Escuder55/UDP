#pragma once
#include "Scene.h"
class Maps :
	public Scene
{
public:
	Maps();
	Maps(int i);
	~Maps();

	void InitSprites();
	void DrawSprites();
	TypeScene DrawScene();
	int CheckButtonClicked(sf::Vector2f posClick);
	void InputControl(sf::RenderWindow* window);

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

};


#pragma once
#include "Scene.h"
class FirstChoice :
	public Scene
{
public:
	FirstChoice();
	FirstChoice(int aux);
	~FirstChoice();

	void InitSprites();
	int CheckButtonClicked(sf::Vector2f _posClick);
	TypeScene DrawScene();
	void DrawSprites();
	void InputControl(sf::RenderWindow* window);

private:
	TypeScene myTypeScene;

	sf::Texture signUpTexture;
	sf::Sprite  signUpSprite;

	sf::Texture logInTexture;
	sf::Sprite  logInSprite;
};


#pragma once
#include "Scene.h"
class Menu :
	public Scene
{
public:
	Menu();
	Menu(int i);
	~Menu();
	TypeScene DrawScene();
	void InitSprites();
	void InitText();
	void DrawSprites();
	void DrawText();
	int CheckButtonClicked(sf::Vector2f posClick);
	void InputControl(sf::RenderWindow* window);
private:
	sf::Texture playTexture;
	sf::Sprite playButton;

	sf::Texture logOutTexture;
	sf::Sprite logOutButton;

	sf::Texture exitTexture;
	sf::Sprite exitButton;

	std::string Title;
	sf::Font myFont;
	sf::Text titleText;

	TypeScene myTypeScene;

};


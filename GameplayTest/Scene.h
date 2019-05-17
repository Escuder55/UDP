#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Constants.h"


class Scene
{
public:
	Scene();
	~Scene();
	void InitWindow();
	void CloseWindow();
	virtual TypeScene DrawScene();

	sf::RenderWindow window;

	TypeScene myTypeScene;

protected:
	virtual void InputControl(sf::RenderWindow* window);
};


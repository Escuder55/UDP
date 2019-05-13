#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::InitWindow()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Never Split The Party");
}

void Scene::CloseWindow()
{
	window.close();
}

TypeScene Scene::DrawScene()
{
	return myTypeScene;
}

void Scene::InputControl(sf::RenderWindow * window)
{
}

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

void Scene::UpdatePartnerPosition(float _posX, float _posY)
{
	partner.setPosition(_posX, _posY);
}

void Scene::InputControl(sf::RenderWindow * window)
{
}

void Scene::sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port)
{
}

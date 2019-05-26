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

void Scene::lerp(float Xinicial, float Xfinal, float Yinicial, float Yfinal, float deltaTime, int StartMovement)
{
	float xFinalLerp;
	float yFinalLerp;
	bool finalLerpOne = false;
	float RangoError = 0.2f;

	//TIMERS LERPS
	//TIMER
	clock_t startTimeLerp;
	clock_t endTimeLerp;
	clock_t clockTicksTakenLerp;
	double timeInSecondsLerp;
	startTimeLerp = clock();

	//VERTICAL
	if (StartMovement == 0)
	{

	}
	//HORIZONTAL
	else
	{

	}
}

void Scene::InputControl(sf::RenderWindow * window)
{
}

void Scene::sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port)
{
}

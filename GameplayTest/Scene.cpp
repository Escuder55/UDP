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

	int iteraciones=100;

	float distX = 0;
	float distY = 0;
	float percent=0;
	//TIMERS LERPS	
	startTimeLerp = clock();
	endTimeLerp = clock();
	clockTicksTakenLerp = endTimeLerp - startTimeLerp;
	timeInSecondsLerp = clockTicksTakenLerp / (double)CLOCKS_PER_SEC;

	distX = Xfinal - Xinicial;
	distY = Yfinal - Yinicial;
	if (StartMovement == 0)
	{
		while (timeInSecondsLerp < 0.2)
		{
			endTimeLerp = clock();
			clockTicksTakenLerp = endTimeLerp - startTimeLerp;
			timeInSecondsLerp = clockTicksTakenLerp / (double)CLOCKS_PER_SEC;

			percent = (timeInSecondsLerp * 10) / 4;
			UpdatePartnerPosition(Xinicial + (distX*percent), partner.getPosition().y);
		}

		while ((timeInSecondsLerp < 0.4))
		{
			endTimeLerp = clock();
			clockTicksTakenLerp = endTimeLerp - startTimeLerp;
			timeInSecondsLerp = clockTicksTakenLerp / (double)CLOCKS_PER_SEC;

			percent = ((timeInSecondsLerp - 0.2) * 10) / 4;
			UpdatePartnerPosition(partner.getPosition().x, Yinicial + (distY*percent));

		}
	}
	else
	{
		while (timeInSecondsLerp < 0.2)
		{
			endTimeLerp = clock();
			clockTicksTakenLerp = endTimeLerp - startTimeLerp;
			timeInSecondsLerp = clockTicksTakenLerp / (double)CLOCKS_PER_SEC;

			percent = (timeInSecondsLerp * 10) / 4;

			UpdatePartnerPosition(partner.getPosition().x, Yinicial + (distY*percent));
		}

		while ((timeInSecondsLerp < 0.4))
		{
			endTimeLerp = clock();
			clockTicksTakenLerp = endTimeLerp - startTimeLerp;
			timeInSecondsLerp = clockTicksTakenLerp / (double)CLOCKS_PER_SEC;

			percent = ((timeInSecondsLerp - 0.2) * 10) / 4;

			UpdatePartnerPosition(Xinicial + (distX*percent), partner.getPosition().y);

		}
	}
}

void Scene::InputControl(sf::RenderWindow * window)
{
}

void Scene::sendPacketCritic(sf::Packet & pack, sf::IpAddress _IP, unsigned short _port)
{
}

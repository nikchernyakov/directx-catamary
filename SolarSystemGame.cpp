#include "SolarSystemGame.h"
#include <iostream>

using namespace DirectX::SimpleMath;

SolarSystemGame::SolarSystemGame() : Game()
{
	
}

SolarSystemGame::~SolarSystemGame()
{
}

void SolarSystemGame::init()
{
	camera = new Camera(this, {0, 0, -10}, {0, 0, 1});
	box1 = new BoxObject(this, {0,0,0}, {0,1,0,1}, 1.0f, 0.6f);
	box2 = new BoxObject(this, {6,0,0}, {1,0,0,1}, 0.5f, 1.0f);
	box2->transform->setParent(box1->transform);
	box3 = new BoxObject(this, {2,0,0}, {1,1,1,1}, 0.2f, 5.0f);
	box3->transform->setParent(box2->transform);
	
	box4 = new BoxObject(this, {10,0,0}, {1,1,1,1}, 0.7f, 0.3f);
}

void SolarSystemGame::update()
{
	while (const auto delta = mouse->ReadRawDelta())
	{
		camera->rotate((float)delta->x * deltaTime, (float)delta->y * -deltaTime);
	}

	if (inputDevice->KeyIsPressed('W'))
	{
		camera->translate({ 0.0f,0.0f,deltaTime });
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		camera->translate({ -deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		camera->translate({ 0.0f,0.0f,-deltaTime });
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		camera->translate({ deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('R'))
	{
		camera->translate({ 0.0f,deltaTime,0.0f });
	}
	if (inputDevice->KeyIsPressed('F'))
	{
		camera->translate({ 0.0f,-deltaTime,0.0f });
	}
}

void SolarSystemGame::drawObjects()
{
	box1->draw();
	box2->draw();
	box3->draw();
	box4->draw();
	//pyramid->draw();
}

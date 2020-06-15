#include "KatamariGame.h"
#include <iostream>

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame() : Game()
{
	
}

KatamariGame::~KatamariGame()
{
}

void KatamariGame::init()
{
	camera = new Camera(this, {0, 0, -10});
	camera->rotate(0, 0);
	model = new ModelObject(this, "Meshes/eyeball/eyeball_obj.obj");
}

void KatamariGame::update()
{
	
	
	while (const auto delta = mouse->ReadRawDelta())
	{
		camera->rotate((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}

	if (inputDevice->KeyIsPressed('W'))
	{
		model->transform->addPosition({ 0.0f,0.0f,deltaTime });
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		model->transform->addPosition({ deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		model->transform->addPosition({ 0.0f,0.0f,-deltaTime });
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		model->transform->addPosition({ -deltaTime,0.0f,0.0f });
	}
	/*if (inputDevice->KeyIsPressed('Q'))
	{
		camera->translate({ 0.0f,deltaTime,0.0f });
	}
	if (inputDevice->KeyIsPressed('E'))
	{
		camera->translate({ 0.0f,-deltaTime,0.0f });
	}*/
}

void KatamariGame::drawObjects()
{
	model->draw();
}

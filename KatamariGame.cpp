#include "KatamariGame.h"
#include <iostream>
#include "KatamariCamera.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame() : Game()
{
	
}

KatamariGame::~KatamariGame()
{
}

void KatamariGame::init()
{
	model = new ModelObject(this, "Meshes/eyeball/eyeball_obj.obj");

	camera = new KatamariCamera(this, {0, 1, -6}, model);
	camera->rotate(0, -2);
	
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

	camera->update();
}

void KatamariGame::drawObjects()
{
	model->draw();
}

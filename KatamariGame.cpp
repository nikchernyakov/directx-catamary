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
	/*plane = new BoxObject(this, { 0, 0, 0 }, 
		{ 1, 1, 1, 1 }, {1, 0.1, 1});*/
	
	katamariSphere = new KatamariSphere(this, "Meshes/eyeball/eyeball_obj.obj", L"Meshes/eyeball/eyes_blue.jpg");
	//katamariSphere->transform->setPosition({ 0, 0.8, 0 });

	camera = new KatamariCamera(this, {0, 0, -6}, katamariSphere);
	//camera->rotate(0, -2);
	
}

void KatamariGame::update()
{
	
	while (const auto delta = mouse->ReadRawDelta())
	{
		camera->rotate((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}

	if (inputDevice->KeyIsPressed('W'))
	{
		katamariSphere->transform->addPosition({ 0.0f, 0.0f, deltaTime });
		katamariSphere->transform->rotate({ 1, 0, 0 }, deltaTime);
		//camera->translate({ 0.0f,0.0f,deltaTime });
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		katamariSphere->transform->addPosition({ deltaTime, 0.0f, 0.0f });
		katamariSphere->transform->rotate({ 0, 0, -1 }, deltaTime);
		//camera->translate({ deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		katamariSphere->transform->addPosition({ 0.0f, 0.0f, -deltaTime });
		katamariSphere->transform->rotate({ -1, 0, 0 }, deltaTime);
		//camera->translate({ 0.0f,0.0f,-deltaTime });
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		katamariSphere->transform->addPosition({ -deltaTime, 0.0f, 0.0f });
		katamariSphere->transform->rotate({ 0, 0, 1 }, deltaTime);
		//camera->translate({ -deltaTime,0.0f,0.0f });
	}

	camera->update();
}

void KatamariGame::drawObjects()
{
	//plane->draw();
	katamariSphere->draw();
	
}

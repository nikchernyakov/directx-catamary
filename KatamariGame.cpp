#include "KatamariGame.h"
#include <iostream>
#include "KatamariCamera.h"
#include "Engine/Texture.h"

using namespace DirectX::SimpleMath;

KatamariGame::KatamariGame() : Game()
{
	
}

KatamariGame::~KatamariGame()
{
}

void KatamariGame::init()
{
	texture = new Texture(this, L"Meshes/eyeball/eyes_blue.jpg");

	D3D11_INPUT_ELEMENT_DESC texturedShaderInputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	texturedShader = new TexturedShader(this, L"Shaders/ShaderTextured.fx", texturedShaderInputElements, 4, texture);

	D3D11_INPUT_ELEMENT_DESC shaderInputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	shader = new Shader(this, L"Shaders/Shader.fx", shaderInputElements, 3);
	
	plane = new BoxObject(this, shader, { 0, 0, 0 }, 
		{ 1, 1, 1, 1 }, {2, 0.1, 2} );

	box1 = new BoxObject(this, shader, { -1, 1, 0 },
		{ 1, 0, 1, 1 }, { 0.1, 0.1, 0.1 });

	box2 = new BoxObject(this, shader, { -0.5, 1, -1 },
		{ 1, 0, 1, 1 }, { 0.1, 0.1, 0.1 });
	
	box3 = new BoxObject(this, shader, { 1, 1, 0 },
		{ 1, 0, 1, 1 }, { 0.1, 0.1, 0.1 });
	
	katamariSphere = new KatamariSphere(this, "Meshes/eyeball/eyeball-mod.obj", texturedShader);

	katamariPlayer = new SceneGameObject(this);
	katamariSphere->transform->setParent(katamariPlayer->transform);
	katamariPlayer->transform->setPosition({ 0, 0.8, 0 });

	camera = new KatamariCamera(this, {0, 1, -6}, katamariSphere);
	camera->rotate(0, -2);
	
}

void KatamariGame::update()
{
	
	/*while (const auto delta = mouse->ReadRawDelta())
	{
		camera->addWorldRotation((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}*/

	if (inputDevice->KeyIsPressed('W'))
	{
		katamariPlayer->transform->addPosition({ 0.0f, 0.0f, deltaTime });
		katamariPlayer->transform->addWorldRotation({ 1, 0, 0 }, deltaTime);
		//katamariPlayer->transform->rotation
		//camera->translate({ 0.0f,0.0f,deltaTime });
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		katamariPlayer->transform->addPosition({ deltaTime, 0.0f, 0.0f });
		katamariPlayer->transform->addWorldRotation({ 0, 0, 1 }, -deltaTime);
		/*Vector3 axisResult = { 0, 0, -1 };
		Vector3::Transform({ 0, 0, -1 }, katamariSphere->transform->updateWorldMatrix(), axisResult);*/
		//katamariSphere->transform->addWorldRotation(axisResult, deltaTime);
		//katamariSphere->transform->rotateAlongAxis(katamariPlayer->transform->GetZVector(), deltaTime);
		//camera->translate({ deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		katamariPlayer->transform->addPosition({ 0.0f, 0.0f, -deltaTime });
		katamariPlayer->transform->addWorldRotation({ 1, 0, 0 }, -deltaTime);
		//camera->translate({ 0.0f,0.0f,-deltaTime });
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		katamariPlayer->transform->addPosition({ -deltaTime, 0.0f, 0.0f });
		katamariPlayer->transform->addWorldRotation({ 0, 0, 1 }, deltaTime);
		//camera->translate({ -deltaTime,0.0f,0.0f });
	}

	katamariSphere->update();
	camera->update();

	collisionCheck(box1);
	collisionCheck(box2);
	collisionCheck(box3);

	
}

void KatamariGame::drawObjects()
{
	plane->draw();
	box1->draw();
	box2->draw();
	box3->draw();
	katamariSphere->draw();
	
}

void KatamariGame::collisionCheck(GameObject* gameObject)
{
	if (gameObject->transform->parent == nullptr && katamariSphere->collider->Contains(gameObject->transform->getWorldPosition()))
	{
		//const auto placementPos = gameObject->transform->getWorldPosition() - katamariSphere->transform->getWorldPosition();
		gameObject->transform->setParent(katamariSphere->transform);
		//gameObject->transform->setPosition(placementPos);

		//auto pos = 

		// goMatrix * -1 Sphere = new matrix
		// new matrix * Sphere
	}
}

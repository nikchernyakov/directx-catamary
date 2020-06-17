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
			12,
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

	texturedShader = new TexturedShader(this, L"Shaders/ShaderTextured.fx", texturedShaderInputElements, 3, texture);

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
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	shader = new Shader(this, L"Shaders/Shader.fx", shaderInputElements, 2);
	
	plane = new BoxObject(this, shader, { 0, 0, 0 }, 
		{ 1, 1, 1, 1 }, {1, 0.1, 1} );
	
	katamariSphere = new KatamariSphere(this, "Meshes/eyeball/eyeball_obj.obj", texturedShader);
	katamariSphere->transform->setPosition({ 0, 0.8, 0 });

	camera = new KatamariCamera(this, {0, 1, -6}, katamariSphere);
	camera->rotate(0, -2);
	
}

void KatamariGame::update()
{
	
	/*while (const auto delta = mouse->ReadRawDelta())
	{
		camera->rotate((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}*/

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
	plane->draw();
	katamariSphere->draw();
	
}

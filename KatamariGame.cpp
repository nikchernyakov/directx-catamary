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
	initDirect2D();
	
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
		camera->addLocalRotation((float)delta->x * -deltaTime, (float)delta->y * deltaTime);
	}*/

	if (inputDevice->KeyIsPressed('W'))
	{
		katamariPlayer->transform->addPosition({ 0.0f, 0.0f, deltaTime });
		katamariPlayer->transform->addLocalRotation({ 1, 0, 0 }, deltaTime);
		//katamariPlayer->transform->rotation
		//camera->translate({ 0.0f,0.0f,deltaTime });
	}
	if (inputDevice->KeyIsPressed('A'))
	{
		katamariPlayer->transform->addPosition({ deltaTime, 0.0f, 0.0f });
		katamariPlayer->transform->addLocalRotation({ 0, 0, 1 }, -deltaTime);
		/*Vector3 axisResult = { 0, 0, -1 };
		Vector3::Transform({ 0, 0, -1 }, katamariSphere->transform->updateWorldMatrix(), axisResult);*/
		//katamariSphere->transform->addLocalRotation(axisResult, deltaTime);
		//katamariSphere->transform->rotateAlongAxis(katamariPlayer->transform->GetZVector(), deltaTime);
		//camera->translate({ deltaTime,0.0f,0.0f });
	}
	if (inputDevice->KeyIsPressed('S'))
	{
		katamariPlayer->transform->addPosition({ 0.0f, 0.0f, -deltaTime });
		katamariPlayer->transform->addLocalRotation({ 1, 0, 0 }, -deltaTime);
		//camera->translate({ 0.0f,0.0f,-deltaTime });
	}
	if (inputDevice->KeyIsPressed('D'))
	{
		katamariPlayer->transform->addPosition({ -deltaTime, 0.0f, 0.0f });
		katamariPlayer->transform->addLocalRotation({ 0, 0, 1 }, deltaTime);
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
	// Direct 2D draw
	pRenderTarget2D->BeginDraw();
	auto rec1 = D2D1::RectF(0.0f, 0.0f, 400, 400);
	auto rec2 = D2D1::RectF(330.0f, 0.0f, 400, 400);
	pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::WhiteSmoke));
	std::wstring header = L"Collected objects:";
	std::wstring count = std::to_wstring(collectedObjectCount);
	/*pRenderTarget2D->DrawTextW(StringHelper::StringToWide(fpsStirng).c_str(), fpsStirng.length(), pDTextFormat.Get(), &rec1, pSolidBrush.Get());
	pRenderTarget2D->DrawTextW(StringHelper::StringToWide(attachedCounterString).c_str(), attachedCounterString.length(), pDTextFormat.Get(), &rec2, pSolidBrush.Get());*/
	
	pRenderTarget2D->DrawTextW(header.c_str(), header.length(), pDTextFormat, &rec1, pSolidBrush);
	pRenderTarget2D->DrawTextW(count.c_str(), count.length(), pDTextFormat, &rec2, pSolidBrush);
	pRenderTarget2D->EndDraw();

	
	// Draw objects 
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
		gameObject->transform->setParent(katamariSphere->transform);
		collectedObjectCount++;
	}
}

void KatamariGame::initDirect2D()
{
	HRESULT hr;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2D1Factory);

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	);

	ID3D11Resource* res;
	rtv->GetResource(&res);

	IDXGISurface* surface;
	hr = res->QueryInterface(__uuidof(IDXGISurface), reinterpret_cast<void**>(&surface));

	hr = pD2D1Factory->CreateDxgiSurfaceRenderTarget(
		surface,
		D2D1_RENDER_TARGET_PROPERTIES{
			D2D1_RENDER_TARGET_TYPE_HARDWARE,
			D2D1_PIXEL_FORMAT {
				/*gammaCorrection ? DXGI_FORMAT_B8G8R8A8_UNORM_SRGB : */DXGI_FORMAT_R8G8B8A8_UNORM,
				D2D1_ALPHA_MODE_PREMULTIPLIED
			},
			static_cast<FLOAT>(96),
			static_cast<FLOAT>(96)
		},
		&pRenderTarget2D
	);
	res->Release();
	surface->Release();

	hr = pRenderTarget2D->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pSolidBrush);

	hr = pDWriteFactory->CreateTextFormat(
		L"arial",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		40.0f,
		L"en-us",
		&pDTextFormat
	);
}

#pragma once
#include <d3d11_1.h>
#include "InputDevice.h"
#include "SimpleMath.h"
#include "Camera.h"
#include "Mouse.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "RenderTexture.h"

using namespace DirectX::SimpleMath;

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void init();
	
	float deltaTime = 0;
	float currentTime = 0;

	int screenWidth = 0;
	int screenHeight = 0;

	const int SHADOW_MAP_SIZE = 1024;

	HWND hWnd;
	
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3DUserDefinedAnnotation* annotation;
	ID3D11Texture2D* depthStencil = NULL;             // �������� ������ ������
	ID3D11DepthStencilView* depthStencilView = NULL;          // ������ ����, ����� ������

	RenderTexture* renderTexture;

	InputDevice* inputDevice;
	Mouse* mouse;
	
	void doFrame();

	Camera* camera;
	Light* light;
	MeshRenderer* meshRenderer;
	
protected:
	virtual void update();
	void render();
	void renderShadowMap();
	virtual void renderShadowMapObjects();
	virtual void drawObjects();
};


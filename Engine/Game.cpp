#include "Game.h"
#include <iostream>

Game::Game()
{
	renderTexture = new RenderTexture();
	
	inputDevice = new InputDevice();
	mouse = new Mouse();
	mouse->EnableRaw();
	
	meshRenderer = new MeshRenderer(this);
}

Game::~Game()
{

}

void Game::init()
{
	renderTexture->init(device, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
}

void Game::doFrame()
{
	update();
	render();
}

void Game::update()
{
	
}

void Game::render()
{
	renderShadowMap();
	
	D3D11_VIEWPORT viewport = {};
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
	context->OMSetRenderTargets(1, &rtv, depthStencilView);
	
	float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	context->ClearRenderTargetView(rtv, color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	annotation->BeginEvent(L"BeginDraw");
	drawObjects();
	annotation->EndEvent();
	
	swapChain->Present(1, 0);
}

void Game::renderShadowMap()
{
	// Set the render target to be the render to texture.
	renderTexture->setRenderTarget(context);

	// Clear the render to texture.
	renderTexture->clearRenderTarget(context, { 0.0f, 0.0f, 0.0f, 1.0f });
	
	renderShadowMapObjects();
}

void Game::renderShadowMapObjects()
{
	
}

void Game::drawObjects()
{
	
}

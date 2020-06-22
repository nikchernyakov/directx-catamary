#pragma once
#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class RenderTexture
{
public:
	RenderTexture();
	~RenderTexture();

	bool init(ID3D11Device*, int textureWidth, int textureHeight);

	void setRenderTarget(ID3D11DeviceContext*);
	void clearRenderTarget(ID3D11DeviceContext*, Vector4);
	ID3D11ShaderResourceView* getShaderResourceView();

private:
	ID3D11Texture2D* m_renderTargetTexture;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11ShaderResourceView* m_shaderResourceView;

	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;

	D3D11_VIEWPORT m_viewport;
	Matrix m_projectionMatrix;
	Matrix m_orthoMatrix;
};


#pragma once
#include <d3d11.h>
#include "GameObject.h"

class Game;

class PrimitiveGameObject : public GameObject
{
public:
	
	PrimitiveGameObject(Game* game, Vector3 position = Vector3::Zero);
	void init() override;
	void update() override;
	void draw() override;

protected:

	std::vector<Vertex> m_vertices;
	std::vector<DWORD> m_indices;
	ComPtr<ID3D11Buffer> pIndexBuffer;
	ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT indicesCount;
	
	ComPtr<ID3D11InputLayout> pInputLayout;
	ComPtr<ID3D11VertexShader> pVertexShader;
	ComPtr<ID3D11PixelShader> pPixelShader;
	ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_SUBRESOURCE_DATA* csd;
	
	Vector4 m_color;

	UINT stride;
	UINT offset = 0u;
};


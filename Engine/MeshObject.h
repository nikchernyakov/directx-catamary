#pragma once

#include <d3d11_1.h>
#include <vector>

#include "Vertex.h"
#include <wrl/client.h>

class Game;
using namespace Microsoft::WRL;

class MeshObject
{
public:
	MeshObject(Game* game,
		std::vector<Vertex>& vertices,
		std::vector<DWORD>& indices,
		D3D11_PRIMITIVE_TOPOLOGY topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void draw();

private:
	Game* m_game;

	UINT indicesCount;
	UINT stride;
	UINT offset = 0u;
	
	D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;
	ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
	ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;

	ComPtr<ID3D11InputLayout> pInputLayout;
	ComPtr<ID3D11VertexShader> pVertexShader;
	ComPtr<ID3D11PixelShader> pPixelShader;
	ComPtr<ID3D11Buffer> pConstantBuffer;
};


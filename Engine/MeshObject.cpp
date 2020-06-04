#include "MeshObject.h"
#include "Game.h"
#include <d3dcompiler.h>
#include <iostream>
#include "ConstantBuffer.h"

MeshObject::MeshObject(Game* game,
                       std::vector<Vertex>& vertices,
                       std::vector<DWORD>& indices,
                       D3D11_PRIMITIVE_TOPOLOGY topology)
{
	HRESULT hr;
	
	m_game = game;
	primitiveTopology = topology;

	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = vertices.size() * sizeof(Vertex);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();

	hr = m_game->device->CreateBuffer(
		&bd,
		&sd,
		pVertexBuffer.GetAddressOf()
	);
	
	stride = sizeof(Vertex);

	// Create Index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = indices.size() * sizeof(DWORD);
	ibd.StructureByteStride = sizeof(DWORD);
	
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	
	hr = m_game->device->CreateBuffer(
		&ibd, 
		&isd, 
		pIndexBuffer.GetAddressOf()
	);
	indicesCount = std::size(indices);

	ID3DBlob* vertexBC;
	ID3DBlob* errorVertexCode;
	auto res = D3DCompileFromFile(L"MiniTri.fx",
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0,
		&vertexBC,
		&errorVertexCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(m_game->hWnd, L"MiniTri.fx", L"Missing Shader File", MB_OK);
		}
		return;
	}

	m_game->device->CreateVertexShader(
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		nullptr,
		&pVertexShader
		);

	//D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* pixelBC;
	ID3DBlob* errorPixelCode;
	res = D3DCompileFromFile(L"MiniTri.fx", 
		nullptr/*Shader_Macros /*macros*/, nullptr /*include*/,
		"PSMain", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0, &pixelBC, &errorPixelCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(m_game->hWnd, L"MiniTri.fx", L"Missing Shader File", MB_OK);
		}
		return;
	}

	m_game->device->CreatePixelShader(
		pixelBC->GetBufferPointer(),
		pixelBC->GetBufferSize(),
		nullptr,
		&pPixelShader
		);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	ID3D11InputLayout* layout;
	hr = m_game->device->CreateInputLayout(
		inputElements,
		2,
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		&pInputLayout);

	CD3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(ConstantBuffer);
	cbd.StructureByteStride = 0u;
	hr = m_game->device->CreateBuffer(&cbd, NULL, &pConstantBuffer);

	//bind constant buffer to vertex shader
	m_game->context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
}

void MeshObject::draw()
{
	m_game->context->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	m_game->context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);

	m_game->context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_game->context->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	m_game->context->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	m_game->context->IASetInputLayout(pInputLayout.Get());

	// Update Constant Buffer
	const ConstantBuffer cb =
	{
		Matrix::Identity,
		m_game->camera->getViewMatrix(),
		m_game->camera->getProjectionMatrix(),
	};
	m_game->context->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);

	m_game->context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	m_game->context->DrawIndexed(indicesCount, 0, 0);
}

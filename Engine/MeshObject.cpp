#include "MeshObject.h"
#include "Game.h"

MeshObject::MeshObject(Game* game,
	std::vector<Vertex>& vertices,
	std::vector<DWORD>& indices,
	D3D11_PRIMITIVE_TOPOLOGY topology)
{
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

	m_game->device->CreateBuffer(
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
	ibd.ByteWidth = indices.size() * sizeof(unsigned short);
	ibd.StructureByteStride = sizeof(unsigned short);
	
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	
	m_game->device->CreateBuffer(
		&ibd, 
		&isd, 
		pIndexBuffer.GetAddressOf()
	);
	indicesCount = std::size(indices);
}

void MeshObject::draw()
{
	m_game->context->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		0u
	);

	m_game->context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	m_game->context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_game->context->DrawIndexedInstanced(indicesCount, 1, 0, 0,0);
}

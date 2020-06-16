#include "Game.h"
#include "ModelObject.h"
#include <WICTextureLoader.h>

ModelObject::ModelObject(Game* game, const std::string& filePath, const wchar_t* texturePath) : GameObject(game)
{
	m_game->meshRenderer->addModel(this, filePath);

	// Загрузка текстуры из файла
	auto hr = DirectX::CreateWICTextureFromFile(m_game->device, texturePath, NULL, &g_pTextureRV, 0);
	
	ModelObject::init();
}

void ModelObject::init()
{
	// Создание сэмпла (описания) текстуры
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Тип фильтрации
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Задаем координаты
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Создаем интерфейс сэмпла текстурирования
	auto hr = m_game->device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
}

void ModelObject::update()
{
}

void ModelObject::draw()
{
	m_game->context->PSSetShaderResources(0, 1, &g_pTextureRV);
	m_game->context->PSSetSamplers(0, 1, &g_pSamplerLinear);
	
	for (MeshObject* meshObject : meshes)
	{
		meshObject->draw();
	}
}

void ModelObject::addMesh(MeshObject* mesh)
{
	meshes.push_back(mesh);
	mesh->transform->setParent(transform);
}

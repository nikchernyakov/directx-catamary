#pragma once
#include "GameObject.h"
#include "MeshObject.h"

class ModelObject : public GameObject
{
public:

	ModelObject(Game* game, const std::string& filePath, const wchar_t* texturePath);

	void init() override;
	void update() override;
	void draw() override;
	void addMesh(MeshObject* mesh);
	
protected:
	
	std::vector<MeshObject*> meshes;

	ID3D11ShaderResourceView* g_pTextureRV = NULL;        // Объект текстуры
	ID3D11SamplerState* g_pSamplerLinear = NULL;    // Параметры наложения текстуры
	
};


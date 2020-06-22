#pragma once
#include "GameObject.h"
#include "MeshObject.h"

class ModelObject : public GameObject
{
public:

	ModelObject(Game* game, const std::string& filePath, Shader* shader);

	void init() override;
	void update() override;
	void draw() override;
	void addMesh(MeshObject* mesh);

	void setShadowMap(ID3D11ShaderResourceView* depthMapTexture);
	
protected:
	
	std::vector<MeshObject*> meshes;
	Shader* m_shader;

	ID3D11ShaderResourceView* m_depthMapTexture;
};


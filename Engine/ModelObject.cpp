#include "Game.h"
#include "ModelObject.h"
#include <WICTextureLoader.h>

ModelObject::ModelObject(Game* game, const std::string& filePath, Shader* shader) : GameObject(game), m_shader(shader)
{
	m_game->meshRenderer->addModel(this, filePath, shader);
	
	ModelObject::init();
}

void ModelObject::init()
{
}

void ModelObject::update()
{
}

void ModelObject::draw()
{
	for (MeshObject* meshObject : meshes)
	{
		meshObject->setShadowMap(m_depthMapTexture);
		meshObject->draw();
	}
}

void ModelObject::addMesh(MeshObject* mesh)
{
	meshes.push_back(mesh);
	mesh->transform->setParent(transform);
}

void ModelObject::renderShadowMapObject(Shader* depthShader)
{
	for (MeshObject* meshObject : meshes)
	{
		meshObject->draw();
	}
}

void ModelObject::setShadowMap(ID3D11ShaderResourceView* depthMapTexture)
{
	m_depthMapTexture = depthMapTexture;
}

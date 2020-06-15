#include "Game.h"
#include "ModelObject.h"

ModelObject::ModelObject(Game* game, const std::string& filePath) : GameObject(game)
{
	m_game->meshRenderer->addModel(this, filePath);
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
		meshObject->draw();
	}
}

void ModelObject::addMesh(MeshObject* mesh)
{
	meshes.push_back(mesh);
}

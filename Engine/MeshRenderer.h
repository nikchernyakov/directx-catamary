#pragma once

#include <d3d11_1.h>

#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "assimp/Importer.hpp"

#include <vector>
#include "Vertex.h"

class Game;
class ModelObject;
class MeshObject;

using namespace Assimp;

class MeshRenderer
{
public:
	MeshRenderer(Game* game);
	
	bool addModel(ModelObject* model, const std::string& filePath);
	void processNode(ModelObject* model, aiNode* node, const aiScene* scene);
	MeshObject* processMesh(aiMesh* mesh, const aiScene* scene);

private:
	Game* m_game;
};


#pragma once

#include <d3d11_1.h>

#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "assimp/Importer.hpp"

#include <vector>
#include "Vertex.h"

class Game;
class MeshObject;

using namespace Assimp;

class MeshRenderer
{
public:
	MeshRenderer(Game* game);
	
	bool AddModel(const std::string& filePath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	MeshObject* ProcessMesh(aiMesh* mesh, const aiScene* scene);

private:
	Game* m_game;
	std::vector<MeshObject*> meshes;
};


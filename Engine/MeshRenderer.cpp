#include "MeshObject.h"
#include "MeshRenderer.h"
#include "assimp/postprocess.h"

MeshRenderer::MeshRenderer(Game* game) : m_game(game)
{
}

bool MeshRenderer::AddModel(const std::string& filePath)
{
    Importer importer;

    const aiScene* pScene = importer.ReadFile(filePath,
        aiProcess_Triangulate |
        aiProcess_ConvertToLeftHanded);

    if (pScene == nullptr)
        return false;

    
    ProcessNode(pScene->mRootNode, pScene);
    return true;
}

void MeshRenderer::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

MeshObject* MeshRenderer::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // Data to fill
    std::vector<Vertex> vertices;
    std::vector<DWORD> indices;

    //Get vertices
    for (UINT i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{
        	Vector3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
        	Vector4{0, 1, 0, 1}
        };

        /*vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;*/

        /*if (mesh->mTextureCoords[0])
        {
            vertex.texCord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCord.y = mesh->mTextureCoords[0][i].y;
        }*/

        vertices.push_back(vertex);
    }

    //Get indices
    for (UINT i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return new MeshObject(m_game, vertices, indices);
}

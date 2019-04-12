#include "resourcemesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QFileDialog>

ResourceMesh::ResourceMesh(unsigned int id) : Resource(RESOURCE_TYPE::RESOURCE_MESH, id)
{

}

void ResourceMesh::LoadResource()
{

}

void ResourceMesh::UnloadResource()
{

}

bool ResourceMesh::LoadModel(const char *fileName)
{
    QFile f(fileName);

    if(!f.open(QFile::ReadOnly))
    {
        f.close();
        return false;
    }

    //
    QByteArray data = f.readAll();

    Assimp::Importer import;

    const aiScene *scene = import.ReadFileFromMemory(
                data.data(), data.size(),
                aiProcess_Triangulate|
                aiProcess_FlipUVs|
                aiProcess_GenSmoothNormals|
                aiProcess_OptimizeMeshes|
                aiProcess_PreTransformVertices|
                aiProcess_ImproveCacheLocality,
                ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    ProcessNode(scene->mRootNode, scene);

    return true;
}

void ResourceMesh::ProcessNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        // load submesh
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }

}

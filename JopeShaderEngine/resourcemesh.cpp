#include "resourcemesh.h"
#include <iostream>

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
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
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
        submeshes.push_back(ProcessMesh(mesh,scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }

}

SubMesh *ResourceMesh::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;

    bool hasTexCoords = false;

    vertices.reserve(mesh->mNumVertices);
    for(int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0])
        {
            hasTexCoords = true;
            vertices.push_back(mesh->mTextureCoords[i]->x);
            vertices.push_back(mesh->mTextureCoords[i]->y);
        }
    }

    indices.reserve(mesh->mNumFaces*3);
    for(int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return nullptr;


}

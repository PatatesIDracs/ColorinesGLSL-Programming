#include "resourcemesh.h"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QFileDialog>
#include <QOpenGLWidget>

ResourceMesh::ResourceMesh(unsigned int id) : Resource(RESOURCE_TYPE::RESOURCE_MESH, id)
{

}

void ResourceMesh::LoadResource()
{
    openGlWidget->makeCurrent();
    for(int i = 0; i < submeshes.size(); i++)
    {
         submeshes[i]->Update();
    }
}

void ResourceMesh::UnloadResource()
{
    for(int i = 0; i < submeshes.size(); i++)
    {
        delete submeshes[i];
    }
    submeshes.clear();
}

bool ResourceMesh::LoadModel(QString fileName)
{
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly))
    {
        std::cout << "Not Read Only" << std::endl;
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

     SetName(fileName.section('/', -1));

    std::cout << "ProcessNode" << std::endl;
    ProcessNode(scene->mRootNode, scene);

    std::cout << "End Porcess Node" << std::endl;

    f.close();

    return true;
}

void ResourceMesh::Bind()
{
    if(isLoaded())
    {
        for (int i = 0; i < submeshes.size(); i++)
        {
            submeshes[i]->Bind();
        }
    }
}

void ResourceMesh::Draw()
{
    if(isLoaded())
    {
        for(uint i = 0; i < submeshes.size(); i++)
        {
            submeshes[i]->Draw();
        }
    }
}

void ResourceMesh::UnBind()
{
    if(isLoaded())
    {
        for (int i = 0; i < submeshes.size(); i++)
        {
            submeshes[i]->UnBind();
        }
    }
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

    vertices.reserve(mesh->mNumVertices*6);
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
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
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

    VertexFormat vertexFormat;
    vertexFormat.SetVertexAttribute(0,0,3);
    vertexFormat.SetVertexAttribute(1,3*sizeof(float), 3);
    if(hasTexCoords)
        vertexFormat.SetVertexAttribute(2,6*sizeof(float), 2);

    return new SubMesh(vertexFormat, &vertices[0], vertices.size()*sizeof(float), &indices[0], indices.size());
}

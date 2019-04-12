#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "resource.h"

class aiNode;
class aiScene;
//class subMesh;

class ResourceMesh : public Resource
{
public:
    ResourceMesh(unsigned int id);
    ~ResourceMesh(){}

    void LoadResource();
    void UnloadResource();

    bool LoadModel(const char* filename);

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    //SubMesh* processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // RESOURCEMESH_H

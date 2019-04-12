#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "resource.h"

struct aiNode;
struct aiScene;
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

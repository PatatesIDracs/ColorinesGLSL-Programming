#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "resource.h"
#include "submesh.h"

#include <QVector>

struct aiNode;
struct aiScene;
struct aiMesh;

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
    SubMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

public:

    QVector<SubMesh*> submeshes;
};

#endif // RESOURCEMESH_H

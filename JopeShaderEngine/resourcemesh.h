#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "resource.h"
#include "submesh.h"


#include <QVector>
class QOpenGLShaderProgram;

struct aiNode;
struct aiScene;
struct aiMesh;

class QOpenGLWidget;

class ResourceMesh : public Resource
{
public:
    ResourceMesh(unsigned int id);
    ~ResourceMesh(){}

    void LoadResource();
    void UnloadResource();

    bool LoadModel(QString fileName);

    void Bind();
    void Draw(QOpenGLShaderProgram* program);
    void UnBind();

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    SubMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

public:
    QOpenGLWidget* openGlWidget;
    QVector<SubMesh*> submeshes;
};

#endif // RESOURCEMESH_H

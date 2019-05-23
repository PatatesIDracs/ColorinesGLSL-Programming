#ifndef COMPMESHRENDERER_H
#define COMPMESHRENDERER_H

#include "component.h"

class ResourceMesh;
class CompTransform;
class MeshRendererUI;

class CompMeshRenderer : public Component
{
public:
    CompMeshRenderer(GameObject* parent, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources);
    ~CompMeshRenderer();

    void UpdateComponent();
    void SetInspectorLayout(QVBoxLayout* inspectorLayout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    int GetMeshID();

public:
    CompTransform* transform;

    ResourceMesh* mesh = nullptr;

    MeshRendererUI* meshRendererUI;

    int textureId = -1;
    int normalId = -1;

};

#endif // COMPMESHRENDERER_H

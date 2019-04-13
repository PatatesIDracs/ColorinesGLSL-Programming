#ifndef COMPMESHRENDERER_H
#define COMPMESHRENDERER_H

#include "component.h"

class ResourceMesh;
class Transform;
class MeshRendererUI;

class CompMeshRenderer : public Component
{
public:
    CompMeshRenderer(GameObject* parent);
    ~CompMeshRenderer();

    void SetInspectorLayout(QVBoxLayout* inspectorLayout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    ResourceMesh* mesh;

    MeshRendererUI* meshRendererUI;

};

#endif // COMPMESHRENDERER_H

#include "compmeshrenderer.h"
#include "meshrendererui.h"

#include "resource.h"
#include "resourcemesh.h"

#include <QVBoxLayout>
#include "comptransform.h"

CompMeshRenderer::CompMeshRenderer(GameObject* parent, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources) : Component (parent, COMP_MESHRENDER)
{
    meshRendererUI = new MeshRendererUI();
    meshRendererUI->SetCompMeshRenderer(this, meshResources);
    transform = static_cast<CompTransform*>(parent->GetComponentByType(COMP_TYPE::COMP_TRANSFORM));
}

CompMeshRenderer::~CompMeshRenderer()
{

}

void CompMeshRenderer::UpdateComponent()
{
    meshRendererUI->UpdateList();
}

void CompMeshRenderer::SetInspectorLayout(QVBoxLayout *inspectorLayout)
{
    inspectorLayout->addWidget(meshRendererUI);
    meshRendererUI->show();
}

void CompMeshRenderer::HideInspectorLayout(QVBoxLayout *inspector_layout)
{
    inspector_layout->removeWidget(meshRendererUI);
    meshRendererUI->hide();
}

int CompMeshRenderer::GetMeshID()
{
    if(mesh != nullptr)
    {
        return mesh->Id();
    }
    else return -1;
}

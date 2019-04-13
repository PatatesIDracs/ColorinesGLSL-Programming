#include "compmeshrenderer.h"
#include "meshrendererui.h"

#include <QVBoxLayout>


CompMeshRenderer::CompMeshRenderer(GameObject* parent) : Component (parent, COMP_MESHRENDER)
{
    meshRendererUI = new MeshRendererUI();
}

CompMeshRenderer::~CompMeshRenderer()
{

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

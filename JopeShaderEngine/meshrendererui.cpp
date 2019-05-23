#include "meshrendererui.h"
#include "ui_meshrendererui.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"
#include "resourcematerial.h"

#include <iostream>

MeshRendererUI::MeshRendererUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererUI)
{
    ui->setupUi(this);

    connect(ui->meshBox, SIGNAL(activated(int)), this, SLOT(ChangeResourceMesh()));
}

MeshRendererUI::~MeshRendererUI()
{
    delete ui;
}

void MeshRendererUI::SetCompMeshRenderer(CompMeshRenderer* newCompMeshRenderer, QVector<ResourceMesh*>* meshResources)
{
    compMeshRenderer = newCompMeshRenderer;
    resourceMeshVector = meshResources;
    UpdateList();
}

void MeshRendererUI::UpdateList()
{
    ui->meshBox->clear();
    ui->meshBox->addItem("(none)", -1);
    for(int i = 0; i < resourceMeshVector->length(); i++)
    {
        ui->meshBox->addItem((*resourceMeshVector)[i]->GetName(), (*resourceMeshVector)[i]->Id());
    }
}

void MeshRendererUI::ChangeResourceMesh()
{
    std::cout << "Change mesh" << std::endl;
    if(ui->meshBox->currentData() == -1)
    {
        compMeshRenderer->mesh = nullptr;
    }

    for(int i = 0; i < resourceMeshVector->length(); i++)
    {
        if((*resourceMeshVector)[i]->Id() == ui->meshBox->currentData())
        {
             compMeshRenderer->mesh = (*resourceMeshVector)[i];
        }
    }


    //TODO: Create submesh combobox

}



#include "meshrendererui.h"
#include "ui_meshrendererui.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"

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
    resourceVector = meshResources;
    UpdateList();
}

void MeshRendererUI::UpdateList()
{
    ui->meshBox->clear();
    ui->meshBox->addItem("(none)", -1);
    for(int i = 0; i < resourceVector->length(); i++)
    {
        ui->meshBox->addItem((*resourceVector)[i]->GetName(), (*resourceVector)[i]->Id());
    }
}

void MeshRendererUI::ChangeResourceMesh()
{
    std::cout << "Change mesh" << std::endl;
    if(ui->meshBox->currentData() == -1)
    {
        compMeshRenderer->mesh = nullptr;
    }

    for(int i = 0; i < resourceVector->length(); i++)
    {
        if((*resourceVector)[i]->Id() == ui->meshBox->currentData())
        {
             compMeshRenderer->mesh = (*resourceVector)[i];
        }
    }    
}



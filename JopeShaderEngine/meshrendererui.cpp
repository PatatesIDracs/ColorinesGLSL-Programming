#include "meshrendererui.h"
#include "ui_meshrendererui.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"
#include "resourcematerial.h"

#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>

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

void MeshRendererUI::SetCompMeshRenderer(CompMeshRenderer* newCompMeshRenderer, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources)
{
    compMeshRenderer = newCompMeshRenderer;
    resourceMeshVector = meshResources;
    resourceMaterialvector = matResources;
    UpdateList();
}

void MeshRendererUI::UpdateList()
{
    ui->meshBox->clear();
    ui->meshBox->addItem("(none)", -1);
    ui->meshBox->setCurrentIndex(0);
    for(int i = 0; i < resourceMeshVector->length(); i++)
    {
        ui->meshBox->addItem((*resourceMeshVector)[i]->GetName(), (*resourceMeshVector)[i]->Id());
        if(compMeshRenderer->mesh != nullptr)
        {
            if(compMeshRenderer->mesh->Id() == (*resourceMeshVector)[i]->Id())
                ui->meshBox->setCurrentIndex(i+1);
        }
    }

    //std::cout << "mesh combobox loaded" << std::endl;
    //Add a combo box for each submesh
    if(compMeshRenderer != nullptr && compMeshRenderer->mesh != nullptr)
    {
        std::cout << "loading material combobox" << std::endl;
        QVector<SubMesh*>* submeshes = &compMeshRenderer->mesh->submeshes;
        for(int i = 0; i < submeshes->length(); i++)
        {
            if(i < materialComboBoxes.length())
                materialComboBoxes[i]->clear();
            else
            {
                materialComboBoxes.push_back(new QComboBox());
                materialLabels.push_back(new QLabel("Submesh " + QString::number(i)));
                materialLayouts.push_back(new QHBoxLayout());
                materialLayouts[i]->addWidget(materialLabels[i]);
                materialLayouts[i]->addWidget(materialComboBoxes[i]);
                ui->meshRendererVlayout->addLayout(materialLayouts[i]);
                connect(materialComboBoxes[i], SIGNAL(activated(int)), this,SLOT(ChangeResourceMaterials()));
            }
            materialComboBoxes[i]->addItem("(none)", -1 );
            for(int j = 0; j < resourceMaterialvector->length(); j++)
            {
                materialComboBoxes[i]->addItem((*resourceMaterialvector)[j]->GetName(), (*resourceMaterialvector)[j]->Id());
            }
        }

        for(int k = submeshes->length(); k < materialComboBoxes.length(); k++)
        {

            ui->meshRendererVlayout[k].removeWidget(materialComboBoxes[k]);
            delete materialComboBoxes[k];
            materialComboBoxes.remove(k);
            ui->meshRendererVlayout[k].removeWidget(materialLabels[k]);
            delete materialLabels[k];
            materialLabels.remove(k);

            delete materialLayouts[k];
            materialLayouts.remove(k);
        }

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
}

void MeshRendererUI::ChangeResourceMaterials()
{
     QVector<SubMesh*>* submeshes = &compMeshRenderer->mesh->submeshes;
    for(int i = 0; i < submeshes->length(); i++)
    {
        if(materialComboBoxes[i]->currentData() == -1)
        {
            (*submeshes)[i]->matResource = nullptr;
        }

        for(int j = 0; j < resourceMaterialvector->length(); j++)
        {
            if((*resourceMaterialvector)[j]->Id() == materialComboBoxes[i]->currentData())
            {
                (*submeshes)[i]->matResource = (*resourceMaterialvector)[j];
            }
        }
    }
}



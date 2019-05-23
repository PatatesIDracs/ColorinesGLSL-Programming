#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "gameobject.h"



#include "comptransform.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"
#include "resourcematerial.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QOpenGLWidget>

#include <iostream>


Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy), count(0), resourceCount(0)
{
    ui->setupUi(this);

    connect(ui->button_addEntity,SIGNAL(clicked()),this,SLOT(CreateNewGO()));
    connect(ui->button_removeEntity, SIGNAL(clicked()), this, SLOT(RemoveGO()));

    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(OnItemClicked()));

}

Hierarchy::~Hierarchy()
{
    qDeleteAll(objects.begin(), objects.end());
    objects.clear();

    //qDeleteAll(resources.begin(), resources.end());
    //resources.clear();

    qDeleteAll(meshResources.begin(), meshResources.end());

    delete ui;
}

void Hierarchy::DrawHierarchy(QWidget* scene)
{
    GameObject* drawnObject = nullptr;
    for(int i = 0; i < objects.size(); i++)
    {
        drawnObject = objects[i];
    }
}

void Hierarchy::CreateNewGO()
{
    count++;
    int numObj = objects.size();

    selected = new GameObject(count, &meshResources, &matResources);
    objects.push_back(selected);

    ui->listWidget->addItem(selected->name);
    ui->listWidget->scrollToBottom();
    ui->listWidget->currentRowChanged(numObj);
    ui->listWidget->setCurrentRow(numObj);

    SigHierarchyUpdate(selected);
    emit SigResourceUpdate(selected);
}

void Hierarchy::RemoveGO()
{
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i] == selected)
        {
            objects.remove(i);
            delete ui->listWidget->takeItem(i);

            (i > 0) ? (i < objects.size())? selected = objects[i]: selected = objects[i-1] : selected = nullptr;

            break;
        }
    }

    SigHierarchyUpdate(selected);
}

void Hierarchy::OnItemClicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();

    int size = ui->listWidget->count();
    for(int i = 0; i < size; i++)
    {
        if(item == ui->listWidget->item(i))
        {
            selected = objects[i];
            break;
        }
    }
    emit SigHierarchyUpdate(selected);
}

void Hierarchy::OnNameChanged()
{
    for(uint i = 0; i < objects.size(); i++)
    {
        if(objects[i] == selected)
        {
            ui->listWidget->item(i)->setText(selected->name);
        }
    }
}

void Hierarchy::CreateNewScene()
{
    // Clear objects QVector
    qDeleteAll(objects.begin(), objects.end());
    objects.clear();

    // Clear listWidget items
    ui->listWidget->clear();

    selected = nullptr;

    count = 0;
}

void Hierarchy::OpenScene()
{
    qDeleteAll(objects.begin(), objects.end());
    objects.clear();

    // Clear listWidget items
    ui->listWidget->clear();

    selected = nullptr;

    // Open file widget
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());

    QFile f(file_name);

    if(!f.open(QFile::ReadOnly))
    {
        return;
    }

    QDataStream stream(&f);
    stream.setVersion(QDataStream::Qt_4_0);

    QString text;
    int numObj;
    stream >> text;
    stream >> count;
    stream >> numObj;

    if(numObj > 0){
        objects.reserve(numObj);
        uint i = 0;
        for(; i < numObj; i++)
        {
            GameObject* temp = new GameObject(i, &meshResources, &matResources);

            temp->Load(stream);

            objects.push_back(temp);
            ui->listWidget->addItem(temp->name);
        }
        ui->listWidget->scrollToBottom();
        ui->listWidget->currentRowChanged(i-1);
        ui->listWidget->setCurrentRow(i-1);

        selected = objects[i-1];
    }

    f.close();
}

void Hierarchy::SaveScene()
{
    std::cout << "Save Scene" << std::endl;

    // SaveScene
    QString file_name = QFileDialog::getSaveFileName(this, "Save file", "");

    if(!file_name.endsWith(".jope"))
        file_name += ".jope";

    QFile f(file_name);

    if(!f.open(QFile::WriteOnly))
    {
        return;
    }

    QDataStream outstream(&f);
    outstream << QString("Scene Gameobjects");
    outstream << count;
    outstream << objects.size();

    outstream.setVersion(QDataStream::Qt_4_0);

    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->Save(outstream);
    }

    f.close();
}

void Hierarchy::OpenFile()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());

    if(file_name.isNull())
    {
        std::cout << "File NULL" << std::endl;
        return;
    }

    resourceCount++;
    ResourceMesh* mesh = new ResourceMesh(resourceCount);
    mesh->openGlWidget = openGLWidget;

    if(mesh->LoadModel(file_name))
    {
        std::cout << "Model Loaded" << std::endl;
        QMessageBox::StandardButton button = QMessageBox::question(
                    this, "Open File Output",
                    "Resource Mesh loaded, do you want to create a GameObject with this resource?");
        if(button == QMessageBox::Yes)
        {
            CreateNewGO();
            CompMeshRenderer* renderer = static_cast<CompMeshRenderer*>(selected->GetComponentByType(COMP_TYPE::COMP_MESHRENDER));

            renderer->mesh = mesh;
            mesh->AddInstance();

        }
        meshResources.push_back(mesh);

    }
    else {
        resourceCount--;
        delete mesh;
    }
}

void Hierarchy::LoadTexture()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());

    if(file_name.isNull())
    {
        std::cout << "File NULL" << std::endl;
        return;
    }

    resourceCount++;
    ResourceMaterial* material = new ResourceMaterial(resourceCount);
    material->openGlWidget = openGLWidget;

    if(material->LoadMaterial(file_name))
    {
        QMessageBox::StandardButton button = QMessageBox::question(
                    this, "Load Material Output",
                    "Resource Material loaded, The texture loaded is a Height Map?");
        if(button == QMessageBox::Yes)
        {
            material->FromHeightMapToNormalMap();
        }

        material->AddInstance();
        matResources.push_back(material);
    }
    else {
        resourceCount--;
        delete material;
    }
}

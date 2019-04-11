#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "gameobject.h"
#include "resource.h"
#include "resourcemesh.h"

#include <QFileDialog>
#include <QDir>

#include <iostream>


Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy), count(0)
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

    selected = new GameObject(count);
    objects.push_back(selected);

    ui->listWidget->addItem(selected->name);
    ui->listWidget->scrollToBottom();
    ui->listWidget->currentRowChanged(numObj);
    ui->listWidget->setCurrentRow(numObj);
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
            GameObject* temp = new GameObject(i);

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

    for(uint i = 0; i < objects.size(); i++)
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
    }

    /*
    resourceCount++;
    ResourceMesh* mesh = new ResourceMesh(resourceCount);

    mesh->LoadModel((const char*)file_name.data());
    resources.push_back(mesh);
    */

}

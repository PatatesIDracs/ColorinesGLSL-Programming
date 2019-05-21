#include "resourcematerial.h"

#include <QFile>
#include <QOpenGLWidget>

ResourceMaterial::ResourceMaterial(unsigned int id) : Resource(RESOURCE_TYPE::RESOURCE_MESH, id)
{

}

void ResourceMaterial::LoadResource()
{
    openGlWidget->makeCurrent();

}

void ResourceMaterial::UnloadResource()
{
}

bool ResourceMaterial::LoadMaterial(QString fileName)
{
    texture = QImage(fileName);

    SetName(fileName.section('/', -1));

    if(texture.isNull())
        return false;
    else return true;
}

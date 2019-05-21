#ifndef RESOURCEMATERIAL_H
#define RESOURCEMATERIAL_H

#include "resource.h"

#include <QImage>

class QOpenGLWidget;

class ResourceMaterial : public Resource
{
public:
    ResourceMaterial(unsigned int id);

    void LoadResource();
    void UnloadResource();

    bool LoadMaterial(QString fileName);

    QOpenGLWidget* openGlWidget;
private:

    QImage texture;

};

#endif // RESOURCEMATERIAL_H

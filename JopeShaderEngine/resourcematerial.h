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

    int GetTexture() { return textureId; }

    void FromHeightMapToNormalMap();

    QOpenGLWidget* openGlWidget;

private:


    QImage image;

    int textureId = -1;

};

#endif // RESOURCEMATERIAL_H

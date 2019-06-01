#ifndef RESOURCEMATERIAL_H
#define RESOURCEMATERIAL_H

#include "resource.h"

#include <QImage>

class QOpenGLWidget;
class QOpenGLTexture;

class ResourceMaterial : public Resource
{
public:
    ResourceMaterial(unsigned int id);

    void LoadResource();
    void UnloadResource();

    bool LoadMaterial(QString fileName);

    int GetTexture() { return textureId; }
    void BindTexture(uint unit);
    void UnBindTexture(uint unit);

    void FromHeightMapToNormalMap();

    QOpenGLWidget* openGlWidget;

private:


    QImage image;
    QOpenGLTexture* texture = nullptr;
    int textureId = -1;

};

#endif // RESOURCEMATERIAL_H

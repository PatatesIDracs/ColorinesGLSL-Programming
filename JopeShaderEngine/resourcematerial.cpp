#include "resourcematerial.h"
#include "openglwidget.h"

#include <QFile>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QMessageBox>

ResourceMaterial::ResourceMaterial(unsigned int id) : Resource(RESOURCE_TYPE::RESOURCE_MESH, id), textureId(-1)
{

}

void ResourceMaterial::LoadResource()
{

    if(textureId == -1){
        openGlWidget->makeCurrent();

        gl->glGenTextures(1,(GLuint*) &textureId);
        gl->glBindTexture(GL_TEXTURE_2D, (GLuint)textureId );

        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gl->glTexImage2D(GL_TEXTURE_2D, 0, image.format(), image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    }
}

void ResourceMaterial::UnloadResource()
{
    if(textureId != -1)
        gl->glDeleteTextures(1,(GLuint*) &textureId);
}

bool ResourceMaterial::LoadMaterial(QString fileName)
{
    image = QImage(fileName);

    SetName(fileName.section('/', -1));

    if(image.isNull())
        return false;
    else return true;

}

void ResourceMaterial::FromHeightMapToNormalMap()
{/*
     QImage normalMap(image.size(), QImage::Format_RGB888);
     const int w = normalMap.width();
     const int h = normalMap.height();
     const float bumpiness = 2.0f;
     for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
        // surrounding indices
        const int il = (x + w - 1) % w;
        const int ir = (x + 1) % w;
        const int ib = (y + 1) % h;
        const int it = (y + w - 1) % h;
        // surrounding pixels
        float tl = qRed( image.pixel(il, it) ) / 255.0f; // top left
        float l = qRed( image.pixel(il, y) ) / 255.0f; // left
        float bl = qRed( image.pixel(il, ib) ) / 255.0f; // bottom left
        float t = qRed( image.pixel(x, it) ) / 255.0f; // top
        float b = qRed( image.pixel(x, ib) ) / 255.0f; // bottom
        float tr = qRed( image.pixel(ir, it) ) / 255.0f; // top right
        float r = qRed( image.pixel(ir, y) ) / 255.0f; // right
        float br = qRed( image.pixel(ir, ib) ) / 255.0f; // bottom right
        // sobel filter
        const float dX = (tl + 2.0 * l + bl) - (tr + 2.0 * r + br);
        const float dY = (bl + 2.0 * b + br) - (tl + 2.0 * t + tr);
        const float dZ = 1.0/bumpiness;
        // normal vector
        QVector3D n(dX, dY, dZ);
        n.normalize();
        n = n* 0.5 + QVector3D(0.5f, 0.5f, 0.5f);
        normalMap.setPixelColor(x, y, QColor::fromRgbF(n.x(), n.y(), n.z()));
        }
     }

     image = normalMap;*/
}

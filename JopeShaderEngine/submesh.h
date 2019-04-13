#ifndef SUBMESH_H
#define SUBMESH_H

#include "vertexformat.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


class SubMesh
{
public:
    SubMesh(VertexFormat newVertexFormat, void *data, int size);
    SubMesh(VertexFormat newVertexFormat, void *data, int size, unsigned int * indices, int indices_size);
    ~SubMesh();

    void Update();
    void Draw();
    void Destroy();

public:

    unsigned char* vertices;
    size_t verticesSize = 0;

    unsigned int* indices;
    size_t indicesSize = 0;

    VertexFormat vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;

    QOpenGLFunctions *glfuncs = nullptr;

};

#endif // SUBMESH_H

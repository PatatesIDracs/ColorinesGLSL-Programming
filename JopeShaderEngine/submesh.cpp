#include "submesh.h"

#include <iostream>

SubMesh::SubMesh(VertexFormat newVertexFormat, void *newData, int vSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    data = new unsigned char[vSize];
    memcpy(data, newData, vSize);
    dataSize = vSize;

}

SubMesh::SubMesh(VertexFormat newVertexFormat, void *newData, int vSize, unsigned int *newIndices, int iSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    data = new unsigned char[vSize];
    memcpy(data, newData, vSize);
    dataSize = vSize;

    indices = new unsigned int[iSize];
    memcpy(indices, newIndices, iSize );
    indicesSize = iSize;
}

SubMesh::~SubMesh()
{
    Destroy();
}

void SubMesh::Update()
{
    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data,int(dataSize));

    delete[] data;
    data = nullptr;

    if(indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indicesSize*sizeof(unsigned int)));

        delete[] indices;
        indices = nullptr;
    }

    for(int location = 0;  location < MAX_VERTEX_ATTRIBUTES; location++)
    {
        VertexAttribute &attr = vertexFormat.attributes[location];

        if(attr.enabled)
        {
            glfuncs->glEnableVertexAttribArray(GLuint(location));
            glfuncs->glVertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)(attr.offset));
        }
    }

    vao.release();
    vbo.release();
    if(ibo.isCreated())
        ibo.release();
}

void SubMesh::Bind()
{
    vao.bind();
}

void SubMesh::UnBind()
{
    vao.release();
}


void SubMesh::Draw()
{
    int numVertices = dataSize/vertexFormat.size;

    vao.bind();
    if(indicesSize > 0)
    {
        std::cout << "Indices = " << indicesSize << "Vertices = " << numVertices << std::endl;
        glfuncs->glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);

        std::cout << "Indices drawn" << std::endl;
    }
    else {
        std::cout << "Vertices > 0" << std::endl;

        glfuncs->glDrawArrays(GL_TRIANGLES, 0, numVertices);

        std::cout << "vertices drawn" << std::endl;
    }
    vao.release();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}

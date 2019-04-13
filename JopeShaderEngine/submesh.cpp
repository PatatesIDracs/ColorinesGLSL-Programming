#include "submesh.h"

SubMesh::SubMesh(VertexFormat newVertexFormat, void *data, int vSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    memcpy(vertices, data, vSize);
    verticesSize = vSize;

}

SubMesh::SubMesh(VertexFormat newVertexFormat, void *data, int vSize, unsigned int *newIndices, int iSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    memcpy(vertices, data, vSize);
    verticesSize = vSize;

    memcpy(indices, newIndices, iSize );
    indicesSize = iSize;
}

SubMesh::~SubMesh()
{

}

void SubMesh::Update()
{
    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices,int(verticesSize));

    delete[] vertices;
    vertices = nullptr;

    if(indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indicesSize));

        delete[] indices;
        indices = nullptr;
    }

    for(int location = 0;  location < MAX_VERTEX_ATTRIBUTES; location++)
    {
        VertexAttribute &attr = vertexFormat.attributes[location];

        if(attr.enabled)
        {
            //glfuncs->glEnableVertexAttribArray(GLuint(location));
            //glfuncs->glVertexAttribPointer(Gluint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)(att.offset));

        }
    }
}

void SubMesh::Draw()
{
    int numVertices = verticesSize/vertexFormat.size;
    vao.bind();
    if(indicesSize > 0)
    {

    }
    else {

    }
    vao.release();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}

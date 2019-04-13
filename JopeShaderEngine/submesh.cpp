#include "submesh.h"

SubMesh::SubMesh(VertexFormat newVertexFormat, void *data, int vSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    memcpy(data, data, vSize);
    dataSize = vSize;

}

SubMesh::SubMesh(VertexFormat newVertexFormat, void *data, int vSize, unsigned int *newIndices, int iSize)
{
    glfuncs = QOpenGLContext::currentContext()->functions();

    vertexFormat = newVertexFormat;

    memcpy(data, data, vSize);
    dataSize = vSize;

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
        ibo.allocate(indices, int(indicesSize));

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

void SubMesh::Draw()
{
    vao.bind();
    if(indicesSize > 0)
    {
        glfuncs->glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
    }
    else {
        int numVertices = dataSize/vertexFormat.size;
        glfuncs->glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }
    vao.release();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}

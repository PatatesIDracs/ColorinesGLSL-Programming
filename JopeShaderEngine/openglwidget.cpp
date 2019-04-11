#include "openglwidget.h"
#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget* parent):
    QOpenGLWidget (parent)
{

    setMinimumSize(parent->window()->size());

}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader1_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader1_frag.frag");
    program.link();
    program.bind();

    //VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f,-0.5f,0.0f),  QVector3D(1.0f,0.0f,0.0f),
        QVector3D(0.5f,-0.5f,0.0f),QVector3D(0.0f,1.0f,.0f),
        QVector3D(0.0f,0.5f,0.0f),QVector3D(0.0f,0.5f,1.0f)
    };
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern((QOpenGLBuffer::UsagePattern::StaticDraw));
    vbo.allocate(vertices, 6*sizeof (QVector3D));

    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2*sizeof (QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof (QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    vao.release();
    vbo.release();
    program.release();

}

void OpenGLWidget::resizeGL(int w, int h)
{
    resize(w,h);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }

}

void OpenGLWidget::finalizeGL()
{
    vao.release();
    vbo.release();
    program.release();
}



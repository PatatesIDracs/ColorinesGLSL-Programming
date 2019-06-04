#include "openglwidget.h"
#include <iostream>

#include "component.h"
#include "comptransform.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"
#include "resourcematerial.h"

#include <QMatrix4x4>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QEvent>
#include <QOpenGLFramebufferObject>

#define sphereH 32
#define sphereV 16

QOpenGLFunctions_3_3_Core * gl = nullptr;

OpenGLWidget::OpenGLWidget(QWidget* parent):
    QOpenGLWidget (parent)
{
    screen_width = width();
    screen_height = height();
    gl = this;
    this->setMouseTracking(true);
    this->setFocus();
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    camera = new CompCamera(nullptr);
    setMinimumSize(parent->window()->size());

    connect(&timer, SIGNAL(timeout()),this,SLOT(UpdateScene()));

   if(format().swapInterval() == -1)
       timer.setInterval(16);
   else
       timer.setInterval(0);
   timer.start();
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

    float quadVertices[] = { -1.0, -1.0, 0.0,       1.0, 1.0, 1.0,      0.0f, 0.0f,
                             1.0, 1.0, 0.0,         1.0, 1.0, 1.0,      1.0f, 1.0f,
                            -1.0, 1.0, 0.0,         1.0, 1.0, 1.0,      0.0f, 1.0f,
                            -1.0, -1.0, 0.0,        1.0, 1.0, 1.0,      0.0f, 0.0f,
                            1.0, -1.0, 0.0,         1.0, 1.0, 1.0,      1.0f, 0.0f,
                            1.0, 1.0, 0.0,          1.0, 1.0, 1.0,      1.0f, 1.0f};


    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex_shader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment_shader.frag");
    program.link();

    InitDefered();

    blurProgram.create();
    blurProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/blur_vert_shader.vert");
    blurProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/blur_frag_shader.frag");
    blurProgram.link();
    blurProgram.bind();

    float quad[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    vboblur.create();
    vboblur.bind();
    vboblur.setUsagePattern((QOpenGLBuffer::UsagePattern::StaticDraw));
    vboblur.allocate(quad, 24*sizeof(float));

    vaoblur.create();
    vaoblur.bind();
    GLint compCount = 2;
    int strideBytes = 4*sizeof (float);
    int offsetBytes0 = 0;
    int offsetBytes1 = sizeof(float) * 2;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));


    vaoblur.release();
    vboblur.release();

    blurProgram.release();

    //Create light program
    lightProgram.create();
    lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/light_vert_shader.vert");
    lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/light_frag_shader.frag");
    lightProgram.link();

    quadProgram.create();
    quadProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/quad_vert_shader.vert");
    quadProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/quad_frag_shader.frag");
    quadProgram.link();
    quadProgram.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern((QOpenGLBuffer::UsagePattern::StaticDraw));
    vbo.allocate(quadVertices, 49*sizeof(float));

    vao.create();
    vao.bind();
    compCount = 3;
    strideBytes = 8*sizeof (float);
    offsetBytes0 = 0;
    offsetBytes1 = sizeof(float) * 3;
    const int offsetBytes2 = sizeof(float) * 6;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));
    glVertexAttribPointer(2,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes2));


    vao.release();
    vbo.release();

    quadProgram.release();


}

void OpenGLWidget::InitDefered()
{
    std::cout << "Hieght:" << screen_height << " Width:" << screen_width << std::endl;
    //Render to texture init
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &normalTexture);
    glBindTexture(GL_TEXTURE_2D, normalTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &posTexture);
    glBindTexture(GL_TEXTURE_2D, posTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, screen_width, screen_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glGenTextures(1, &partialBlurTexture);
    glBindTexture(GL_TEXTURE_2D, partialBlurTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, colorTexture,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D, normalTexture,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D, posTexture,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, depthTexture,0);

    glGenFramebuffers(1, &blurfbo);
    glBindFramebuffer(GL_FRAMEBUFFER, blurfbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, partialBlurTexture,0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch (status)
    {
    case GL_FRAMEBUFFER_COMPLETE://Everything'sOK
        qDebug() << "Framebuffer is Veri gut patates amb suc";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        qDebug() << "FramebufferERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        qDebug() << "Framebuffer ERROR:GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        qDebug()<<"Framebuffer ERROR:GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        qDebug()<<"Framebuffer ERROR:GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        qDebug()<<"Framebuffer ERROR:GL_FRAMEBUFFER_UNSUPPORTED";
        break;
    default:
        qDebug() << "Framebuffer ERROR: Unknown ERROR";
        break;
    }
}

void OpenGLWidget::BlurShader()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if(blurProgram.bind())
    {
       glBindFramebuffer(GL_FRAMEBUFFER,blurfbo);
       glDrawBuffer(GL_COLOR_ATTACHMENT0);

       blurProgram.setUniformValue("colorTexture", 0 );
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, colorTexture);

       blurProgram.setUniformValue("texCoordsInc", 1.0/screen_width, 0);
       vaoblur.bind();
       glDrawArrays(GL_TRIANGLES, 0, 6);
       vaoblur.release();

       glBindFramebuffer(GL_FRAMEBUFFER, 0);

       glBindFramebuffer(GL_FRAMEBUFFER,fbo);
       glDrawBuffer(GL_COLOR_ATTACHMENT0);

       blurProgram.setUniformValue("colorTexture", 0 );
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, partialBlurTexture);

       blurProgram.setUniformValue("texCoordsInc", 0, 1.0/screen_height);
       vaoblur.bind();
       glDrawArrays(GL_TRIANGLES, 0, 6);
       vaoblur.release();


       blurProgram.release();
    }

}

void OpenGLWidget::UpdateScene()
{
    camera->Update();
    update();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    std::cout << "Aspect ratio" << w << h << std::endl;

    resize(w,h);
    camera->SetAspectRatio(w,h);
    screen_width = w;
    screen_height = h;

    glDeleteTextures(1, &colorTexture);
    glDeleteTextures(1, &normalTexture);
    glDeleteTextures(1, &posTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteTextures(1, &partialBlurTexture);

    glDeleteFramebuffers(1, &fbo);
    glDeleteFramebuffers(1, &blurfbo);

    InitDefered();
}

void OpenGLWidget::paintGL()
{
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    glClearDepth(1.0);
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3,buffers);

    if(program.bind())
    {
        program.setUniformValue("projectionMatrix", camera->GetProjectionMatrix());
        QMatrix4x4 cameraTransfrom = camera->GetViewMatrix();

        ResourceMesh* rMesh = nullptr;

        program.setUniformValue("albedoTexture", 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        int previous = -1;
        QMap<unsigned int, CompMeshRenderer*>::iterator i;
        for(i = objects.begin(); i != objects.end(); i++)
        {

            CompMeshRenderer* compMesh = i.value();

            if(compMesh->GetMeshID() < 0)
                continue;

            program.setUniformValue("worldViewMatrix", cameraTransfrom * compMesh->parent->GetTransform()->GetGlobalTransform());
            rMesh = compMesh->mesh;            

            if(rMesh)
            {
                rMesh->Draw();
            }

        }
       program.release();
    }

    BlurShader();

    QOpenGLFramebufferObject::bindDefault();



   //lightProgram.bind();
   //lightProgram.setUniformValue("colorTex", 0);
   //lightProgram.setUniformValue("normalTex", 1);
   //lightProgram.setUniformValue("posTex", 2);
   //glActiveTexture(GL_TEXTURE0);
   //glBindTexture(GL_TEXTURE_2D, colorTexture);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, normalTexture);
   //glActiveTexture(GL_TEXTURE2);
   //glBindTexture(GL_TEXTURE_2D, posTexture);
   //
   //vao.bind();
   //glDrawArrays(GL_TRIANGLES, 0, 6);
   //vao.release();
   //
   //glBindTexture(GL_TEXTURE_2D, 0);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, 0);
   //glActiveTexture(GL_TEXTURE0);
   //glBindTexture(GL_TEXTURE_2D, 0);
   //lightProgram.release();

   glClearColor(0.0f,0.0f,0.0f,1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   quadProgram.bind();
   quadProgram.setUniformValue("colorTexture", 0);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, colorTexture);
   vao.bind();
   glDrawArrays(GL_TRIANGLES, 0, 6);
   vao.release();
   quadProgram.release();

}

void OpenGLWidget::AddGameObject(GameObject *obj)
{
    std::cout << "Add GameObject" << std::endl;
    if(obj)
    {
        std::cout << "GameObject not null" << std::endl;
        CompMeshRenderer* renderer = static_cast<CompMeshRenderer*>(obj->GetComponentByType(COMP_TYPE::COMP_MESHRENDER));
        if(renderer)
        {
           objects.insert(static_cast<unsigned int>(obj->id),renderer);
           std::cout << "insert GO" << std::endl;

        }
    }
}

void OpenGLWidget::finalizeGL()
{
    //vao.release();
    //vbo.release();
    program.release();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        camera->MoveCamera(QVector3D(0,0,1));
    }
    if(event->key() == Qt::Key_S)
    {
        camera->MoveCamera(QVector3D(0,0,-1));
    }
    if(event->key() == Qt::Key_A)
    {
        camera->MoveCamera(QVector3D(-1,0,0));
    }
    if(event->key() == Qt::Key_D)
    {
        camera->MoveCamera(QVector3D(1,0,0));
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{

}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    //0 = left //// 1 = right

    if(event->button() == 1)
    {
        camera_rotate = true;
    }

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x_motion = event->x() - mouse_x;
    mouse_y_motion = event->y() - mouse_y;
    mouse_x = event->x();
    mouse_y = event->y();

    if(camera_rotate)
        camera->RotateCamera(mouse_x_motion,mouse_y_motion);

}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == 1)
    {
        camera_rotate = false;
    }

}



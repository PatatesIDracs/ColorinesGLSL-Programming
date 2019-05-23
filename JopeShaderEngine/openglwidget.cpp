#include "openglwidget.h"
#include <iostream>

#include "component.h"
#include "comptransform.h"
#include "compmeshrenderer.h"
#include "resourcemesh.h"

#include <QMatrix4x4>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QEvent>

#define sphereH 32
#define sphereV 16

OpenGLWidget::OpenGLWidget(QWidget* parent):
    QOpenGLWidget (parent)
{
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

    program.create();
    //program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader1_vert.vert");
    //program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader1_frag.frag");
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex_shader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment_shader.frag");
    program.link();
    program.bind();

    //VBO
/*    QVector3D vertices[] = {
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
    vbo.release();*/
    //DrawTestSphere();
    program.release();

}

void OpenGLWidget::DrawTestSphere()
{
    static const float pi = 3.1416f;
    struct Vertex { QVector3D pos; QVector3D norm; };

    Vertex sphere[sphereH][sphereV + 1];
    for (int h = 0; h < sphereH; ++h)
    {
        for (int v = 0; v < sphereV + 1; ++v)
        {
            float nh = float(h)/ sphereH;
            float nv = float(v)/ sphereV - 0.5f;
            float angleh = 2 * pi * nh;
            float anglev = - pi * nv;
            sphere[h][v].pos.setX(sinf(angleh)*cosf(anglev));
            sphere[h][v].pos.setY(-sinf(anglev));
            sphere[h][v].pos.setZ(cosf(angleh) * cosf(anglev));
            sphere[h][v].norm = sphere[h][v].pos;
        }
    }

    unsigned int sphereIndices[sphereH][sphereV][6];
    for (unsigned int h = 0; h < sphereH; ++h)
    {
        for(unsigned int v = 0; v < sphereV; ++v)
        {
            sphereIndices[h][v][0] = (h+0) * (sphereV+1) + v;
            sphereIndices[h][v][1] = ((h+1)%sphereH) * (sphereV+1) + v;
            sphereIndices[h][v][2] = ((h+1)%sphereH) * (sphereV+1) + v + 1;
            sphereIndices[h][v][3] = (h+0) * (sphereV+1) + v;
            sphereIndices[h][v][4] = ((h+1)%sphereH) * (sphereV+1) + v + 1;
            sphereIndices[h][v][5] = (h+0) * (sphereV+1) + v + 1;
        }
    }

    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern((QOpenGLBuffer::UsagePattern::StaticDraw));
    std::cout << "1" << std::endl;
    std::cout << "sphere size 1= " << sizeof (sphere) << std::endl;
    vbo.allocate(sphere[0], sizeof(sphere));


    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    ibo.allocate(sphereIndices[0], int((sphereH*sphereV*6)*sizeof(unsigned int)));
     std::cout << "2" << std::endl;

    const GLint compCount = 3;
    const int strideBytes = 2*sizeof (QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof (QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));
    std::cout << "3" << std::endl;
    vao.release();
    vbo.release();
    ibo.release();
     std::cout << "4" << std::endl;

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

}

void OpenGLWidget::paintGL()
{
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    if(program.bind())
    {
        program.setUniformValue("projectionMatrix", camera->GetProjectionMatrix());
        QMatrix4x4 cameraTransfrom = camera->GetViewMatrix();


        ResourceMesh* rMesh = nullptr;

        int previous = -1;
        QMap<unsigned int, CompMeshRenderer*>::iterator i;
        for(i = objects.begin(); i != objects.end(); i++)
        {

            CompMeshRenderer* compMesh = i.value();

            if(compMesh->GetMeshID() < 0)
                continue;

            program.setUniformValue("worldViewMatrix", cameraTransfrom * compMesh->parent->GetTransform()->GetGlobalTransform());
            rMesh = compMesh->mesh;
            /*if(i.key() != previous)
            {
                if(rMesh)
                    rMesh->UnBind();
                previous = i.key();

                rMesh = compMesh->mesh;
                if(rMesh)
                {
                    rMesh->Bind();
                }

            }*/

            if(rMesh)
            {
                rMesh->Draw();
            }
            // Bind Textures



        }

        if(rMesh != nullptr)
            rMesh->UnBind();

       //vao.bind();
       //std::cout << "Going to draw sphere" << std::endl;
       //glDrawElements(GL_TRIANGLES, (sphereH*sphereV*6), GL_UNSIGNED_INT, nullptr);
       //std::cout << "Not crashed" << std::endl;
       //vao.release();

       //vao.bind();
       //glDrawArrays(GL_TRIANGLES, 0, 3);
       //vao.release();
       program.release();
       //std::cout << "DrawArray" << std::endl;
    }

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



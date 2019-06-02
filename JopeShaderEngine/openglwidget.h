#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QMap>
#include <QTimer>

#include "gameobject.h"
#include "compcamera.h"

class CompMeshRenderer;

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
class QEvent;

class OpenGLWidget :
        public QOpenGLWidget,
        protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget() override;


    //Virtual methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void DrawTestSphere();

    void InitDefered();

    QVector<ResourceMaterial*>* matResources;

signals:

public slots:
    void UpdateScene();
    void AddGameObject(GameObject* obj);
    void finalizeGL();

private:

    QOpenGLBuffer ibo;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram quadProgram;

    QMap<unsigned int, CompMeshRenderer*> objects;




    CompCamera* camera = nullptr;

    QTimer timer;


    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    //void wheelEvent(QWheelEvent* event) override;
    //void enterEvent(QEvent* event) override;
    //void leaveEvent(QEvent* event) override;


    float mouse_x = 0;
    float mouse_y = 0;
    float mouse_x_motion = 0;
    float mouse_y_motion = 0;
    bool camera_rotate = false;

    //paint textures
    GLuint colorTexture;
    GLuint depthTexture;
    GLuint fbo;

    int screen_width;
    int screen_height;
};

extern QOpenGLFunctions_3_3_Core *gl;

#endif // OPENGLWIDGET_H

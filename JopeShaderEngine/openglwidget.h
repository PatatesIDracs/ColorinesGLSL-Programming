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

    QMap<unsigned int, CompMeshRenderer*> objects;

    CompCamera* camera = nullptr;

    QTimer timer;

};

#endif // OPENGLWIDGET_H

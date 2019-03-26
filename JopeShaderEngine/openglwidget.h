#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>

class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class QOpenGLShaderProgram;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget() override;


    //Virtual methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

public slots:

    void finalizeGL();

private:

    QOpenGLBuffer* vbo;
    QOpenGLVertexArrayObject* vao;
    QOpenGLShaderProgram* program;

};

#endif // OPENGLWIDGET_H

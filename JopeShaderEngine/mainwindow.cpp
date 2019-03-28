#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglwidget.h"

#include <QOpenGLWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openGLWidget = new OpenGLWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

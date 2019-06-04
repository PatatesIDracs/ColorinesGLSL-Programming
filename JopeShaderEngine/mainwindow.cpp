#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglwidget.h"
#include "hierarchy.h"
#include "inspector.h"

#include <QOpenGLWidget>
#include <QResizeEvent>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hierarchy = new Hierarchy(nullptr, ui->openGLWidget);
    ui->dock_hierarchy->setWidget(hierarchy);
    inspector = new Inspector();
    ui->dock_inspector->setWidget(inspector);

    connect(inspector,SIGNAL(SigNameChanged()), hierarchy, SLOT(OnNameChanged()));
    connect(ui->actionOpenFile, SIGNAL(triggered()), hierarchy, SLOT(OpenFile()));
    connect(ui->actionLoadTexture, SIGNAL(triggered()), hierarchy, SLOT(LoadTexture()));
    connect(hierarchy,SIGNAL(SigHierarchyUpdate(GameObject*)), inspector, SLOT(ItemSelected(GameObject*)));
    connect(hierarchy, SIGNAL(SigResourceUpdate(GameObject*)), ui->openGLWidget, SLOT(AddGameObject(GameObject*)));
    connect(ui->openGLWidget, SIGNAL(OpenGLInitialized()), hierarchy, SLOT(InitBaseModel()));

    //Displat modes
    connect(ui->actionColor, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayColor()));
    connect(ui->actionNormal, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayNormals()));
    connect(ui->actionPosition, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayPosition()));
    connect(ui->actionDepth, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayDepth()));
    connect(ui->actionFinal_Light, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayLight()));
    connect(ui->actionBlur, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayBlur()));
    connect(ui->actionDepth_of_Field, SIGNAL(triggered()), ui->openGLWidget, SLOT(SetDisplayDoF()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    size.setWidth(size.width() - ui->dock_hierarchy->size().width());

    resizeDocks({ui->dockWidget}, {size.width()}, Qt::Horizontal);
}

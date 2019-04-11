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

    hierarchy = new Hierarchy();
    ui->dock_hierarchy->setWidget(hierarchy);

    inspector = new Inspector();
    ui->dock_inspector->setWidget(inspector);

    connect(inspector,SIGNAL(SigNameChanged()), hierarchy, SLOT(OnNameChanged()));

    connect(ui->actionOpenFile, SIGNAL(triggered()), hierarchy, SLOT(OpenFile()));

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
    ui->openGLWidget->resizeGL(size.width(), size.height());
}

#include "meshrendererui.h"
#include "ui_meshrendererui.h"

MeshRendererUI::MeshRendererUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererUI)
{
    ui->setupUi(this);
}

MeshRendererUI::~MeshRendererUI()
{
    delete ui;
}

#include "transformui.h"
#include "ui_transformui.h"

TransformUI::TransformUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformUI)
{
    ui->setupUi(this);
}

TransformUI::~TransformUI()
{
    delete ui;
}

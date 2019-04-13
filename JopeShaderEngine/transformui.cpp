#include "transformui.h"
#include "ui_transformui.h"
#include "comptransform.h"

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

void TransformUI::SetCompTransform(CompTransform *newCompTransform)
{
    compTransform = newCompTransform;

    connect(ui->posXSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangePosition()));
    connect(ui->posYSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangePosition()));
    connect(ui->posZSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangePosition()));
    connect(ui->rotXSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeRotation()));
    connect(ui->rotYSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeRotation()));
    connect(ui->rotZSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeRotation()));
    connect(ui->scaleXSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeScale()));
    connect(ui->scaleYSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeScale()));
    connect(ui->scaleZSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ChangeScale()));
}

void TransformUI::ChangePosition()
{
    if(compTransform == nullptr)
        return;
    compTransform->SetPosition(QVector3D(ui->posXSpinBox->value(),ui->posYSpinBox->value(),ui->posZSpinBox->value()));
}

void TransformUI::ChangeRotation()
{
    if(compTransform == nullptr)
        return;
    compTransform->SetEulerRotation(QVector3D(ui->rotXSpinBox->value(),ui->rotYSpinBox->value(),ui->rotZSpinBox->value()));
}

void TransformUI::ChangeScale()
{
    if(compTransform == nullptr)
        return;
    compTransform->SetScale(QVector3D(ui->scaleXSpinBox->value(),ui->scaleYSpinBox->value(),ui->scaleZSpinBox->value()));
}

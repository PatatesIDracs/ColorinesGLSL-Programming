#include "comptransform.h"
#include "transformui.h"
#include <QVBoxLayout>
#include <iostream>

CompTransform::CompTransform(GameObject* parent) : Component(parent, COMP_TRANSFORM)
{
    transformLocal.setToIdentity();
    transformGlobal.setToIdentity();
    transformUI = new TransformUI();
    transformUI->SetCompTransform(this);
}

CompTransform::~CompTransform()
{

}

void CompTransform::SetInspectorLayout(QVBoxLayout *inspectorLayout)
{
    std::cout << "Adding trans ui" << std::endl;
    inspectorLayout->addWidget(transformUI);
    transformUI->show();
}

void CompTransform::HideInspectorLayout(QVBoxLayout *inspector_layout)
{
    inspector_layout->removeWidget(transformUI);
    transformUI->hide();
}

QMatrix4x4 CompTransform::GetLocalTransform() const
{
    return transformLocal;
}

QMatrix4x4 CompTransform::GetGlobalTransform()
{
    if(parent->parent != nullptr)
        transformGlobal = parent->parent->GetTransform()->GetGlobalTransform() * transformLocal;
    else
        transformGlobal = transformLocal;

    return transformGlobal;
}

const QQuaternion CompTransform::GetRotQuat() const
{
    return rotation;
}

const QVector3D CompTransform::GetRotAngles() const
{
    return rotAngles;
}

const QVector3D CompTransform::GetPosition() const
{
    return position;
}

const QVector3D CompTransform::GetScale() const
{
    return scale;
}

void CompTransform::SetTransform(QMatrix4x4 newTransform)
{
    transformLocal = newTransform;
    transformGlobal = newTransform;
}

void CompTransform::SetTransform(QVector3D pos, QQuaternion rot)
{
    position = pos;
    rotation = rot.normalized();
    rotAngles = rotation.toEulerAngles();

    ReCalculateTransform();
}

void CompTransform::SetPosition(QVector3D newPos)
{
    position = newPos;
    ReCalculateTransform();
}

void CompTransform::SetRotation(QQuaternion newRot)
{
    rotation = newRot;
    rotAngles = rotation.toEulerAngles();
    ReCalculateTransform();
}

void CompTransform::SetEulerRotation(QVector3D newEulerAngles)
{
    rotAngles = newEulerAngles;
    rotation = QQuaternion::fromEulerAngles(rotAngles);
    ReCalculateTransform();
}

void CompTransform::SetScale(QVector3D newScale)
{
    scale = newScale;
    ReCalculateTransform();
}

void CompTransform::ReCalculateTransform()
{
    transformLocal.setToIdentity();
    transformLocal.translate(position);
    transformLocal.rotate(rotation);
    transformLocal.scale(scale);
    std::cout << "Recalculation transform" << std::endl;
    std::cout << "trueposX" << transformLocal.column(3).x() << "posY" << transformLocal.column(3).y() << "posZ" << transformLocal.column(3).z() << std::endl;
}


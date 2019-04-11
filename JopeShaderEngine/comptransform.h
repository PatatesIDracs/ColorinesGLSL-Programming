#ifndef COMPTRANSFORM_H
#define COMPTRANSFORM_H

#include "component.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>

class TransformUI;

class CompTransform : public Component
{

public:
    CompTransform(GameObject* parent);
    ~CompTransform();

    void SetInspectorLayout(QVBoxLayout* inspectorLayout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    //Getters
    const QMatrix4x4 GetLocalTransform() const;
    const QMatrix4x4 GetGlobalTransform() const;
    const QQuaternion GetRotQuat() const;
    const QVector3D GetRotAngles() const;
    const QVector3D GetPosition() const;
    const QVector3D GetScale() const;

    //Setters
    void SetTransform(QMatrix4x4 newTransform);
    void SetTransform(QVector3D pos, QQuaternion rot);
    void SetPosition(QVector3D newPos);
    void SetRotation(QQuaternion newRot);
    void SetEulerRotation(QVector3D newEulerAngles);
    void SetScale(QVector3D newScale);

    void ReCalculateTransform();

private:

    QMatrix4x4 transformLocal, transformGlobal;
    QQuaternion rotation = QQuaternion(1,0,0,0);

    QVector3D position = QVector3D(0,0,0);
    QVector3D rotAngles = QVector3D(0,0,0);
    QVector3D scale = QVector3D(1,1,1);

    TransformUI* transformUI;

};

#endif // COMPTRANSFORM_H

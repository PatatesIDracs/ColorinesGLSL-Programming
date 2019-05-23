#include "compcamera.h"

#include <qmath.h>
#include <iostream>

CompCamera::CompCamera(GameObject* parent) : Component(parent, COMP_CAMERA)
{
    position = QVector3D(0,0,5);
    prepareMatrices();
}

CompCamera::~CompCamera()
{

}

QVector4D CompCamera::getLeftRightBottomTop()
{
    return QVector4D(0,0,0,0);
}

QVector3D CompCamera::screenPointToWorldRay(int x, int y)
{
    return QVector3D(0,0,0);
}

QMatrix4x4 CompCamera::GetWorldMatrix()
{
    return worldMatrix;
}

QMatrix4x4 CompCamera::GetViewMatrix()
{
    return viewMatrix;
}

QMatrix4x4 CompCamera::GetProjectionMatrix()
{
    return projectionMatrix;
}

void CompCamera::Update()
{

}

void CompCamera::prepareMatrices()
{
    //viewMatrix.setToIdentity();
    //worldMatrix.setToIdentity();


    //viewMatrix.lookAt(position, QVector3D(0,0,0),QVector3D(0,1,0));
    //worldMatrix = viewMatrix.inverted();

    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw,QVector3D(0,1,0));
    worldMatrix.rotate(pitch,QVector3D(1,0,0));
    viewMatrix = worldMatrix.inverted();


    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy,aspectRatio,zNear,zFar);
}

void CompCamera::SetAspectRatio(int width, int height)
{
    aspectRatio = float(width)/float(height);
    std::cout << aspectRatio << std::endl;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy, aspectRatio, zNear, zFar);
}

void CompCamera::MoveCamera(QVector3D movement)
{

    QVector3D moveVec = QVector3D(0.0f, 0.0f, 0.0f);
    //press W
    if(movement == QVector3D(0,0,1))
    {
        moveVec += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                         sinf(qDegreesToRadians(pitch)),
                         -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    //press S
    if(movement == QVector3D(0,0,-1))
    {
        moveVec += QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                            -sinf(qDegreesToRadians(pitch)),
                            cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    //press A
    if(movement == QVector3D(-1,0,0))
    {
        moveVec += QVector3D(-cosf(qDegreesToRadians(yaw)),
                             0.0f,
                             sinf(qDegreesToRadians(yaw)));
    }

    //press D
    if(movement == QVector3D(1,0,0))
    {
        moveVec += QVector3D(cosf(qDegreesToRadians(yaw)),
                             0.0f,
                             -sinf(qDegreesToRadians(yaw)));
    }


    position += moveVec;
    prepareMatrices();

}

void CompCamera::RotateCamera(float dx, float dy)
{
    yaw -= dx;
    pitch -= dy;
    prepareMatrices();
}

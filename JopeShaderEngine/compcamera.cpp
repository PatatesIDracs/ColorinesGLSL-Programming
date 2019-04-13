#include "compcamera.h"

CompCamera::CompCamera(GameObject* parent) : Component(parent, COMP_CAMERA)
{
    position = QVector3D(1,1,1);
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

void CompCamera::prepareMatrices()
{
    viewMatrix.lookAt(position, QVector3D(0,0,0),QVector3D(0,1,0));
    worldMatrix = viewMatrix.inverted();
    projectionMatrix.perspective(fovy,aspectRatio,zNear,zFar);
}

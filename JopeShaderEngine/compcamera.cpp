#include "compcamera.h"

CompCamera::CompCamera(GameObject* parent) : Component(parent, COMP_CAMERA)
{
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

void CompCamera::prepareMatrices()
{

}

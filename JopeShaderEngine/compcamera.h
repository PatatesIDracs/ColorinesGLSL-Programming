#ifndef COMPCAMERA_H
#define COMPCAMERA_H

#define DEFAULT_CAMERA_FOVY 60
#define DEFAULT_CAMERA_ZNEAR 0.5f
#define DEFAULT_CAMERA_ZFAR 100.0f
#define DEFAULT_CAMERA_SPEED 10.0f
#define DEFAULT_ASPECT_RATIO 1.77f

#include "component.h"

#include <QVector3D>
#include <QMatrix4x4>


class QVector2D;
class QVector4D;

class CompCamera : Component
{
public:
    CompCamera(GameObject* parent);
    ~CompCamera();

    QVector4D getLeftRightBottomTop();

    QVector3D screenPointToWorldRay(int x, int y);

    QMatrix4x4 GetWorldMatrix();
    QMatrix4x4 GetViewMatrix();
    QMatrix4x4 GetProjectionMatrix();

    void prepareMatrices();

private:

    int viewportWidth = 256;
    int viewportHeight = 256;

    float fovy = DEFAULT_CAMERA_FOVY;
    float aspectRatio = DEFAULT_ASPECT_RATIO;
    float zNear = DEFAULT_CAMERA_ZNEAR;
    float zFar = DEFAULT_CAMERA_ZFAR;

    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    float speed= DEFAULT_CAMERA_SPEED;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;
};

#endif // COMPCAMERA_H

#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameobject.h"

class QVBoxLayout;

enum COMP_TYPE
{
    COMP_UNKNOWN,
    COMP_TRANSFORM,
    COMP_MESHRENDER,
    COMP_CAMERA
};


class Component
{
public:
    Component(GameObject* parent, COMP_TYPE type);
    virtual ~Component();


    virtual void SetInspectorLayout(QVBoxLayout* inspectorLayout);
    virtual void HideInspectorLayout(QVBoxLayout* inspector_layout);

public:
    GameObject* parent;

    COMP_TYPE type = COMP_UNKNOWN;

};

#endif // COMPONENT_H

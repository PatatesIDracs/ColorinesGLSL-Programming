#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameobject.h"

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


public:
    GameObject* parent;

    COMP_TYPE type = COMP_UNKNOWN;

};

#endif // COMPONENT_H

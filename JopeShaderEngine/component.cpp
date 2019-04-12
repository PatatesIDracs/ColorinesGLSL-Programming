#include "component.h"

#include <QVBoxLayout>

Component::Component(GameObject* parent, COMP_TYPE type) : parent(parent), type(type)
{

}

Component::~Component()
{

}

void Component::SetInspectorLayout(QVBoxLayout *inspectorLayout)
{
    return;
}

void Component::HideInspectorLayout(QVBoxLayout *inspector_layout)
{
    return;
}

#include "gameobject.h"
#include "component.h"
#include "comptransform.h"
#include <QDataStream>
#include <iostream>


GameObject::GameObject(int i)
{
    name = "New GameObject ";
    name.append(QString::number(i));

    components.push_back(new CompTransform(this));
}

void GameObject::Save(QDataStream &outstream)
{

}

void GameObject::Load(QDataStream &stream)
{

}

void GameObject::SetInspectorLayout(QVBoxLayout *inspector_layout)
{
    for (int i=0; i < components.size(); i++)
    {
        components[i]->SetInspectorLayout(inspector_layout);
    }
}

void GameObject::HideInspectorLayout(QVBoxLayout *inspector_layout)
{
    for (int i=components.size()-1; i >= 0; i--)
    {
        components[i]->HideInspectorLayout(inspector_layout);
    }
}

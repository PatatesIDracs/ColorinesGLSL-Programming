#include "gameobject.h"
#include "component.h"
#include "comptransform.h"
#include <QDataStream>
#include <iostream>

#include "compmeshrenderer.h"


GameObject::GameObject(int i)
{
    name = "New GameObject ";
    name.append(QString::number(i));

    components.push_back(new CompTransform(this));
    components.push_back(new CompMeshRenderer(this));
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

Component *GameObject::GetComponentByType(COMP_TYPE comp_type)
{
    for (int i = 0; i < components.size(); i++)
    {
        if(components[i]->type == comp_type)
            return  components[i];
    }
    return nullptr;
}

#include "gameobject.h"
#include "component.h"
#include "comptransform.h"
#include <QDataStream>
#include <iostream>

#include "compmeshrenderer.h"


GameObject::GameObject(int i, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources, GameObject* parent) :parent(parent)
{
    id = i;
    name = "New GameObject ";
    name.append(QString::number(i));

    if(parent != nullptr)
        parent->childs.push_back(this);

    components.push_back(new CompTransform(this));
    components.push_back(new CompMeshRenderer(this, meshResources, matResources));
}

GameObject::~GameObject()
{
    if(parent!= nullptr)
        parent->childs.removeOne(this);
    qDeleteAll(childs.begin(), childs.end());
    childs.clear();
}

void GameObject::Save(QDataStream &outstream)
{

}

void GameObject::Load(QDataStream &stream)
{

}

void GameObject::UpdateComponents()
{
    for (int i=0; i < components.size(); i++)
    {
        components[i]->UpdateComponent();
    }
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

CompTransform *GameObject::GetTransform()
{
    return (CompTransform*)GetComponentByType(COMP_TRANSFORM);
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

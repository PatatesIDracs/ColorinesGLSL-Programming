#include "gameobject.h"
#include <QDataStream>
#include <iostream>


GameObject::GameObject(int i)
{
    name = "New GameObject ";
    name.append(QString::number(i));

}

void GameObject::Save(QDataStream &outstream)
{

}

void GameObject::Load(QDataStream &stream)
{

}

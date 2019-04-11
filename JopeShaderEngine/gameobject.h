#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QVector>

class QDataStream;
class Component;
class QVBoxLayout;

class GameObject
{
public:
    GameObject(int i);

    void Save(QDataStream &stream);
    void Load(QDataStream &stream);


    void SetInspectorLayout(QVBoxLayout* inspector_layout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

public:
    QString name;

    QVector<Component*> components;

};

#endif // GAMEOBJECT_H

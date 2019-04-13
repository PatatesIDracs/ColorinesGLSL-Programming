#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QVector>

class QDataStream;
class QVBoxLayout;
class Component;
enum COMP_TYPE;

class GameObject
{
public:
    GameObject(int i);

    void Save(QDataStream &stream);
    void Load(QDataStream &stream);


    void SetInspectorLayout(QVBoxLayout* inspector_layout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    Component *GetComponentByType(COMP_TYPE comp_type);

public:
    QString name;

    QVector<Component*> components;

};

#endif // GAMEOBJECT_H

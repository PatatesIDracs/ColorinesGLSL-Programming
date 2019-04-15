#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QVector>

class QDataStream;
class QVBoxLayout;
class Component;
class CompTransform;
enum COMP_TYPE;

class GameObject
{
public:
    GameObject(int i, GameObject* parent = nullptr);
    ~GameObject();

    void Save(QDataStream &stream);
    void Load(QDataStream &stream);


    void SetInspectorLayout(QVBoxLayout* inspector_layout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    CompTransform *GetTransform();
    Component *GetComponentByType(COMP_TYPE comp_type);

public:
    QString name;
    GameObject* parent;

    QVector<Component*> components;
    QVector<GameObject*> childs;

};

#endif // GAMEOBJECT_H

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QVector>

class QDataStream;
class QVBoxLayout;
class Component;
class CompTransform;
class ResourceMesh;
class ResourceMaterial;
enum COMP_TYPE;

class GameObject
{
public:
    GameObject(int i, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources, GameObject* parent = nullptr);
    ~GameObject();

    void Save(QDataStream &stream);
    void Load(QDataStream &stream);

    void UpdateComponents();
    void SetInspectorLayout(QVBoxLayout* inspector_layout);
    void HideInspectorLayout(QVBoxLayout* inspector_layout);

    CompTransform *GetTransform();
    Component *GetComponentByType(COMP_TYPE comp_type);

public:
    int id;
    QString name;
    GameObject* parent;

    QVector<Component*> components;
    QVector<GameObject*> childs;

};

#endif // GAMEOBJECT_H

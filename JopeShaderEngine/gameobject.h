#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

class QDataStream;

class GameObject
{
public:
    GameObject(int i);

    void Save(QDataStream &stream);
    void Load(QDataStream &stream);


public:
    QString name;
};

#endif // GAMEOBJECT_H

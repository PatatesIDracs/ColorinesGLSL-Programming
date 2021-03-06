#ifndef RESOURCE_H
#define RESOURCE_H

enum RESOURCE_TYPE
{
    NO_TYPE,
    RESOURCE_MESH,
    RESOURCE_TEXTURE
};

#include <QString>

class Resource
{
public:
    Resource(RESOURCE_TYPE type, unsigned int id);
    virtual ~Resource();

    unsigned int Id(){ return id; }

    void SetName(QString newName) { name = newName; }
    QString GetName(){ return name; }

    virtual void LoadResource(){}
    virtual void UnloadResource(){}

    void AddInstance();
    void RemoveInstance();

    bool isLoaded() { return loaded; }
    unsigned int numInstances() { return count; }

private:
    RESOURCE_TYPE type;
    QString name;

    unsigned int id = 0;

    bool loaded = false;
    unsigned int count = 0;

};

#endif // RESOURCE_H

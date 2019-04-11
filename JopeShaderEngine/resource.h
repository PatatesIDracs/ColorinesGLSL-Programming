#ifndef RESOURCE_H
#define RESOURCE_H

enum RESOURCE_TYPE
{
    NO_TYPE,
    RESOURCE_MESH,
    RESOURCE_TEXTURE
};


class Resource
{
public:
    Resource(RESOURCE_TYPE type);
    ~Resource();

    virtual void LoadResource();
    virtual void UnloadResource();

    void AddInstance();
    void RemoveInstance();

private:
    bool isLoaded() { return count > 0; }

private:
    RESOURCE_TYPE type;

    unsigned int count = 0;
};

#endif // RESOURCE_H

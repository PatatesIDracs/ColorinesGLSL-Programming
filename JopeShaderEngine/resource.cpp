#include "resource.h"

Resource::Resource(RESOURCE_TYPE newType, unsigned int newId) : type(newType), id(newId)
{

}

Resource::~Resource()
{
    if(isLoaded())
        UnloadResource();
}

void Resource::AddInstance()
{
    if(!loaded)
    {
        LoadResource();
        loaded = true;
    }

    count++;
}

void Resource::RemoveInstance()
{
    if(count > 0)
        count--;
}

#include "resource.h"

Resource::Resource(RESOURCE_TYPE newType) : type(newType)
{

}

Resource::~Resource()
{

}

void Resource::LoadResource()
{

}

void Resource::UnloadResource()
{

}

void Resource::AddInstance()
{
    if(count == 0)
        LoadResource();

    count++;
}

void Resource::RemoveInstance()
{
    if(count > 0)
        count--;


    if(count == 0)
        UnloadResource();

}

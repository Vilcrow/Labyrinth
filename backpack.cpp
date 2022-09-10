#include "backpack.h"

BackpackObject* BackpackObject::uniqueInstance = nullptr;

BackpackObject::BackpackObject() : capacity(maxCapacity)
{

}

BackpackObject* BackpackObject::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new BackpackObject();
    return uniqueInstance;
}

bool BackpackObject::addObject(LabyrinthObject *obj)
{
    if(capacity > 0) {
        inventory.push_back(obj);
        --capacity;
        return true;
    }
    return false; //backpack is full;
}

bool BackpackObject::removeObject(LabyrinthObject *obj)
{
    //check the presence of an object in the backpack
    //and remove it
}

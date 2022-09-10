#include "backpack.h"

BackpackObject::BackpackObject() : capacity(maxCapacity)
{

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
    return false;
}

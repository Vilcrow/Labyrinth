#include "backpack.h"

BackpackObject* BackpackObject::uniqueInstance = nullptr;

BackpackObject::BackpackObject() : cpt(maxCapacity)
{

}

BackpackObject* BackpackObject::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new BackpackObject();
    return uniqueInstance;
}

void BackpackObject::add(LabyrinthObject *obj)
{
    if(cpt > 0) {
        inventory.push_back(obj);
        --cpt;
    }
    else {
        //say to player that the backpack is full
    }
}

void BackpackObject::remove(LabyrinthObject *obj)
{
    //check the presence of an object in the backpack
    //and remove it
}

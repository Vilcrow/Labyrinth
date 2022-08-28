#include "backpack.h"

Backpack::Backpack() : capacity(maxCapacity)
{

}

Backpack::~Backpack()
{

}

void Backpack::addObject(LabyrinthObject obj)
{
    if(capacity > 0) {
        inventory.push_back(obj);
        --capacity;
    }
}

void Backpack::removeObject(LabyrinthObject obj)
{
    //check the presence of an object in the backpack
    //and remove it
}

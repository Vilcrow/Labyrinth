#include <string>
#include "door.h"

DoorObject::DoorObject(int num, bool opnd)
                      : LabyrinthObject(Labyrinth::ObjectDoor)
                      , number(num), opened(opnd)
{

}

bool DoorObject::open(const KeyObject& key)
{
    if(number == key.getNumber()) {
        opened = true;
        return true;
    }
    else //key don't worked
        return false;
}

std::string DoorObject::handleAction(const Action& act)
{
    return "OK";
}

std::string KeyObject::handleAction(const Action& act)
{
    return "OK";
}

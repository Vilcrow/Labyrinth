#include <string>
#include "door.h"

DoorObject::DoorObject(int num, bool opnd)
                      : LabyrinthObject(Labyrinth::ObjectDoor)
                      , nmbr(num), opened(opnd)
{

}

bool DoorObject::open(const KeyObject& key)
{
    if(nmbr == key.number()) {
        opened = true;
        return true;
    }
    else //key don't worked
        return false;
}

const std::string DoorObject::action(Labyrinth::ActionType type)
{
    switch(type) {
    case Labyrinth::ActionNone:
        return std::string("Impossible");
    case Labyrinth::ActionClose:
        if(opened) {
            opened = false;
            return std::string("Door closed.");
        }
        else
            return std::string("Door already closed.");
    case Labyrinth::ActionOpen:
        if(!opened) {
            opened = true;
            return std::string("Door opened.");
        }
        else
            return std::string("Door already opened.");
    case Labyrinth::ActionInspect:
        return std::string("Door with number " + std::to_string(nmbr) + ".");
    }
    return std::string("Impossible");
}

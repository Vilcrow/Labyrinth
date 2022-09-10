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

std::string DoorObject::handleAction(const Action& act) //need elaboration
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionClose:
        if(!opened)
            result = "Door already closed.";
        else {
            opened = false;  //good idea?
            result = "You close the door.";
        }
        break;
    case Labyrinth::ActionOpen:
        if(opened)
            result = "Door already opened.";
        else {
            opened = true;
            result = "You open the door.";
        }
        break;
    case Labyrinth::ActionInspect:
        result = "You see door with number ";
        result += std::to_string(number) + ".";
        break;
    default:
        result = "Impossible.";
    }
    return result;
}

std::string KeyObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = "You see key with number ";
        result += std::to_string(number) + ".";
        break;
    default:
        result = "Impossible.";
    }
    return result;
}

#include "wall.h"

WallObject::WallObject() : LabyrinthObject(Labyrinth::ObjectWall)
{

}

void WallObject::addObject(LabyrinthObject *obj)
{
    objects.push_back(obj);
}

std::string WallObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = "You see: ";
        if(objects.empty())
            result += "empty wall";
        else {
            for(auto o : objects) {
                result += o->getName();
                result += ", ";
            }
            result[result.size()-2] = '.';
        }
        break;
    case Labyrinth::ActionOpen:
    case Labyrinth::ActionClose:
    case Labyrinth::ActionTake:
    case Labyrinth::ActionUse:
    default:
        result = "Impossible. You can just inspect the wall.";
    }
    return result;
}

LabyrinthObject* WallObject::findObject(Labyrinth::ObjectType type)
{
    if(objects.empty())
        return nullptr;
    for(auto o : objects) {
        if(o->getType() == type) 
            return o;
    }
    return nullptr;
}

#include <algorithm>
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
    return "OK";
}

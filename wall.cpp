#include <algorithm>
#include "wall.h"

WallObject::WallObject() : LabyrinthObject(Labyrinth::ObjectWall)
{

}

void WallObject::add(LabyrinthObject obj)
{
    objects.push_back(obj);
}

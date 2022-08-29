#include "wall.h"

WallObject::WallObject(/*Labyrinth::WallType tp*/)
                       : LabyrinthObject(Labyrinth::ObjectWall)
                       /*, type(tp)*/
{

}

void WallObject::addObject(LabyrinthObject obj)
{
    objects.push_back(obj);
}

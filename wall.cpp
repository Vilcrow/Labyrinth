#include "wall.h"

WallObject::WallObject(Labyrinth::WallType tp)
                       : LabyrinthObject(Labyrinth::ObjectWall)
                       , type(tp)
{

}

#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , number(num)
{
    top = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}
/*
void RoomObject::addObject(Labyrinth::WallType wall, LabyrinthObject obj)
{
    switch(wall) {
    case Labyrinth::WallTop:
        top.push_back(obj);
        break;
    case Labyrinth::WallDown:
        top.push_back(obj);
        break;
    case Labyrinth::WallLeft:
        top.push_back(obj);
        break;
    case Labyrinth::WallRight:
        top.push_back(obj);
        break;
    }
}
*/

void RoomObject::addWall(Labyrinth::WallType type,
                         std::shared_ptr<WallObject> wall)
{
    switch(type) {
    case Labyrinth::WallTop:
        if(!top)
            top = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallDown:
        if(!down)
            down = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallLeft:
        if(!left)
            left = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallRight:
        if(!right)
            right = wall;
        else {
            //need error handling
        }
    }
}

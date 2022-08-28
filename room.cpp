#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , number(num)
{

}

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

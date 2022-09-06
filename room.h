#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include <memory>
#include "labyrinth.h"
#include "wall.h"

class RoomObject : public LabyrinthObject {
    int nmbr;
    std::shared_ptr<WallObject> top;
    std::shared_ptr<WallObject> down;
    std::shared_ptr<WallObject> left;
    std::shared_ptr<WallObject> right;
public:
    RoomObject(int num);
    virtual ~RoomObject() {}
    void wall(Labyrinth::WallType type, std::shared_ptr<WallObject> wall);
    void add(Labyrinth::WallType wall, LabyrinthObject obj);
    int number() const { return nmbr; }
    std::shared_ptr<WallObject> wall(Labyrinth::WallType type);
};

#endif

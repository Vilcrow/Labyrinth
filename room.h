#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include <memory>
#include "labyrinth.h"
#include "wall.h"

class RoomObject : public LabyrinthObject {
    int number;
    std::shared_ptr<WallObject> top;
    std::shared_ptr<WallObject> down;
    std::shared_ptr<WallObject> left;
    std::shared_ptr<WallObject> right;
public:
    RoomObject(int num);
    virtual ~RoomObject() {}
    void setProperties() override {}
    void addWall(Labyrinth::WallType type, std::shared_ptr<WallObject> wall);
    void addObject(Labyrinth::WallType wall, LabyrinthObject obj);
    int getNumber() const { return number; }
};

#endif

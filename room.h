#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include <memory>
#include "labyrinth.h"
#include "wall.h"

class RoomObject : public LabyrinthObject {
    WallObject *top;
    WallObject *down;
    WallObject *left;
    WallObject *right;
    WallObject *currentWall;
    Labyrinth::WallType wallType;
public:
    RoomObject();
    virtual ~RoomObject();
    void addObject(Labyrinth::WallType wall, LabyrinthObject *obj);
    void setCurrentWall(Labyrinth::WallType type);
    WallObject* getCurrentWall() { return currentWall; }
    Labyrinth::WallType getCurrentWallType() { return wallType; }
    std::string handleAction(const Action& act) override;
    std::string getName() const override { return "room"; }
};

#endif

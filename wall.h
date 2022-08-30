#ifndef WALL_H_SENTRY
#define WALL_H_SENTRY

#include <vector>
#include "labyrinth.h"

class WallObject : public LabyrinthObject {
    //Labyrinth::WallType type;
    std::vector<LabyrinthObject> objects;
public:
    WallObject(/*Labyrinth::WallType tp*/);
    virtual ~WallObject() {}
    void setProperties() {}
    void addObject(LabyrinthObject obj);
};

#endif

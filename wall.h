#ifndef WALL_H_SENTRY
#define WALL_H_SENTRY

#include <vector>
#include "labyrinth.h"

class WallObject : public LabyrinthObject {
    std::vector<LabyrinthObject*> objects;
public:
    WallObject();
    virtual ~WallObject() {}
    void addObject(LabyrinthObject *obj);
    std::string handleAction(const Action& act) override;
};

#endif

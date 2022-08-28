#ifndef BACKPACK_H_SENTRY
#define BACKPACK_H_SENTRY

#include <vector>
#include "labyrinth.h"

class Backpack {
    int capacity;
    std::vector<LabyrinthObject> inventory;
    enum { maxCapacity = 6 };
public:
    Backpack();
    ~Backpack();
    void addObject(LabyrinthObject obj);
    void removeObject(LabyrinthObject obj);
    int getCapacity() const { return capacity; }
};

#endif

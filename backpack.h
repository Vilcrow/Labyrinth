#ifndef BACKPACK_H_SENTRY
#define BACKPACK_H_SENTRY

#include <vector>
#include "labyrinth.h"

class BackpackObject {
    enum { maxCapacity = 6 };
    int capacity;
    std::vector<LabyrinthObject*> inventory;
public:
    BackpackObject();
    ~BackpackObject() = delete;
    bool addObject(LabyrinthObject *obj);
    bool removeObject(LabyrinthObject *obj);
    int getCapacity() const { return capacity; }
private:
    BackpackObject(BackpackObject& other) = delete;
    BackpackObject& operator=(BackpackObject& other) = delete;
};

#endif

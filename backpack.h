#ifndef BACKPACK_H_SENTRY
#define BACKPACK_H_SENTRY

#include <vector>
#include "labyrinth.h"

//singleton pattern
class BackpackObject {
    enum { maxCapacity = 6 };
    int capacity;
    std::vector<LabyrinthObject> inventory;
public:
    static BackpackObject* instance();
    void addObject(LabyrinthObject obj);
    void removeObject(LabyrinthObject obj);
    int getCapacity() const { return capacity; }
private:
    BackpackObject();
    ~BackpackObject() = delete;
    BackpackObject(BackpackObject& other) = delete;
    BackpackObject& operator=(BackpackObject& other) = delete;
protected:
    static BackpackObject *uniqueInstance;
};

#endif

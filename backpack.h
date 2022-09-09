#ifndef BACKPACK_H_SENTRY
#define BACKPACK_H_SENTRY

#include <vector>
#include "labyrinth.h"

//singleton pattern
class BackpackObject {
    enum { maxCapacity = 6 };
    int cpt;
    std::vector<LabyrinthObject*> inventory;
public:
    static BackpackObject* instance();
    void add(LabyrinthObject *obj);
    void remove(LabyrinthObject *obj);
    int capacity() const { return cpt; }
private:
    BackpackObject();
    ~BackpackObject() = delete;
    BackpackObject(BackpackObject& other) = delete;
    BackpackObject& operator=(BackpackObject& other) = delete;
protected:
    static BackpackObject *uniqueInstance;
};

#endif

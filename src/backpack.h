/*******************************************************************************
** vim:ts=4:sw=4:expandtab
**
** This file is part of the labyrinth project, a text adventure game
**
** Copyright (C) 2022 S.V.I 'Vilcrow', <vilcrow.net>
**
** LICENCE:
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#ifndef BACKPACK_H_SENTRY
#define BACKPACK_H_SENTRY

#include <vector>
#include "labyrinth.h"
#include "key.h"

class BackpackContainer : public LabyrinthContainer {
    enum { maxCapacity = 6 };
    int capacity;
    std::vector<LabyrinthObject*> inventory;
public:
    BackpackContainer();
    virtual ~BackpackContainer() = default;
    bool addObject(LabyrinthObject *obj) override;
    bool removeObject(LabyrinthObject *obj) override;
    int getCapacity() const { return capacity; }
    LabyrinthObject* findObject(const Action act) override;
    KeyObject* findKey(int num);
    std::string getName() const override { return "backpack"; };
    const std::vector<LabyrinthObject*>& getObjects() const { return inventory; }
private:
    BackpackContainer(BackpackContainer& other) = delete;
    BackpackContainer& operator=(BackpackContainer& other) = delete;
};

#endif

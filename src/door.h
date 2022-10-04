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

#ifndef DOOR_H_SENTRY
#define DOOR_H_SENTRY

#include "labyrinth.h"

class Door : public LbrContainer {
public:
    Door(int num);
    virtual ~Door() = default;
    bool addLock(LbrLock *lock);
    int getNumber() const { return number; }
    bool isLocked() const;
    bool addObject(LbrObject *obj) override;
    bool removeObject(LbrObject *obj) override;
    LbrObject* findObject(const Action act) override;
    std::string getNameString() const override { return "door"; }
private:
    enum { maxCapacity = 3 };
    int number;
    std::vector<LbrLock*> locks;
};

#endif

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

#include <string>
#include "sheet.h"
#include "backpack.h"

SheetObject::SheetObject(const std::string& rec)
                            : LabyrinthObject(Labyrinth::ObjectSheet)
                            , record(rec)
{

}

std::string SheetObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = "Record: ";
        result += record + ".";
        break;
    case Labyrinth::ActionTake:
        if(static_cast<BackpackContainer*>(act.backpack)->getCapacity() == 0)
            result = "The backpack is full.";
        else if(act.wall->removeObject(this)) {
            act.backpack->addObject(this);
            result = "Done.";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(act.backpack->removeObject(this)) {
            act.wall->addObject(this);
            result = "Done.";
        }
        else {
            result = "No such item.";
        }
        break;
    default:
        result = "Impossible.";
    }
    return result;
}

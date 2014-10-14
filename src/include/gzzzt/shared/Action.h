/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GZZZT_ACTION_H
#define	GZZZT_ACTION_H

#include <gzzzt/shared/ActionType.h>
#include <gzzzt/shared/Position.h>

namespace gzzzt {

    class Action {
    public:
        ActionType getType() const;
        Position getPosition() const;

    protected:
        explicit Action(ActionType type, Position pos);
        
    private:
        ActionType m_type;
        Position m_pos;
    };
}

#endif	// GZZZT_ACTION_H

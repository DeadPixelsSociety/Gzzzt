/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GZZZT_SERVER_PHYSICS_H
#define GZZZT_SERVER_PHYSICS_H

#include <vector>

#include <gzzzt/server/Body.h>

namespace gzzzt {

    class Physics {
    public:

        void addBody(Body *body);

        void update(float dt);

    private:
        std::vector<Body *> m_dynamic_bodies;
        std::vector<Body *> m_static_bodies;
    };

}

#endif // GZZZT_SERVER_PHYSICS_H

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
#ifndef GZZZT_GAME_H
#define GZZZT_GAME_H

#include <memory>
#include <vector>

#include <gzzzt/server/ServerEntity.h>

namespace gzzzt {

    class Game {
    public:
        void addEntity(std::shared_ptr<ServerEntity> e);
        void removeEntity(std::shared_ptr<ServerEntity> e);

        void update(float dt);


    private:
      std::vector<std::shared_ptr<ServerEntity>> m_entities;

    };
}

#endif // GZZZT_GAME_H

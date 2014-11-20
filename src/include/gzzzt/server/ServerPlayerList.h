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
#ifndef GZZZT_SERVER_PLAYER_LIST_H
#define GZZZT_SERVER_PLAYER_LIST_H

#include <list>

#include <SFML/Network.hpp>

#include <gzzzt/server/ServerPlayer.h>

namespace gzzzt {

    class ServerPlayerList {
    public:
        explicit ServerPlayerList();
        virtual ~ServerPlayerList();

        bool add(gzzzt::ServerPlayer* player);
        void remove(gzzzt::ServerPlayer* player);

        gzzzt::ServerPlayer* getById(uint8_t id) const;
        uint8_t getSize() const;

        // Custom iterators to use foreach
        std::list<gzzzt::ServerPlayer*>::iterator begin();
        std::list<gzzzt::ServerPlayer*>::iterator end();
        std::list<gzzzt::ServerPlayer*>::const_iterator begin() const;
        std::list<gzzzt::ServerPlayer*>::const_iterator end() const;

    private:
        std::list<gzzzt::ServerPlayer*> m_players;

        bool isDuplicatedName(const std::string& name) const;
    };

}

#endif // GZZZT_SERVER_PLAYER_LIST_H

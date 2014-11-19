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
#include <gzzzt/server/ServerPlayerList.h>

namespace gzzzt {

    ServerPlayerList::ServerPlayerList() {
    }

    ServerPlayerList::~ServerPlayerList() {
        for (auto player : m_players) {
            delete player;
        }
        m_players.clear();
    }

    bool ServerPlayerList::add(gzzzt::ServerPlayer* player) {
        m_players.push_back(player);
        return true;
    }

    void ServerPlayerList::remove(gzzzt::ServerPlayer* player) {
        m_players.remove(player);
    }

    gzzzt::ServerPlayer* ServerPlayerList::getById(uint8_t id) const {
        for (auto player : m_players) {
            if (player->getID() == id) {
                return player;
            }
        }
        return nullptr;
    }

    std::list<gzzzt::ServerPlayer*>::iterator ServerPlayerList::begin() {
        return m_players.begin();
    }
    
    std::list<gzzzt::ServerPlayer*>::iterator ServerPlayerList::end() {
        return m_players.end();
    }
    
    std::list<gzzzt::ServerPlayer*>::const_iterator ServerPlayerList::begin() const {
        return m_players.begin();
    }
    
    std::list<gzzzt::ServerPlayer*>::const_iterator ServerPlayerList::end() const {
        return m_players.end();
    }
}

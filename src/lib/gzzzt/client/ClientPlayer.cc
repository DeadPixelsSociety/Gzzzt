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
#include <gzzzt/client/ClientPlayer.h>

namespace gzzzt {

    ClientPlayer::ClientPlayer(std::string name, uint8_t id)
    : m_name(name), m_id(id) {
    }
    
    std::string ClientPlayer::getName() const {
        return m_name;
    }
    
    uint8_t ClientPlayer::getID() const {
        return m_id;
    }
    
    void ClientPlayer::update(float dt) {
        // TODO
    }

    void ClientPlayer::render(sf::RenderWindow& window) {
        // TODO
    }

}

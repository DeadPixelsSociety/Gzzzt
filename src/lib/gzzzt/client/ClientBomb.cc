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
#include <gzzzt/client/ClientBomb.h>

namespace gzzzt {
    ClientBomb::ClientBomb(const sf::Vector2f & position) 
    : ClientEntity()
    , m_remainingTime(0.0f)
    , m_hasExploded(false)
    {
        m_shape.setRadius(30);
        m_shape.setFillColor(sf::Color::Black);
        m_shape.setPosition(position);
    }

    ClientBomb::~ClientBomb() {

    }

    void ClientBomb::update(float dt) {
        
        m_remainingTime += dt;
        
        if (m_remainingTime > BOMB_EXPLODE_TIME) {
            m_hasExploded = true;
        }
    }

    void ClientBomb::render(sf::RenderWindow& window) {
        // TODO
    }
    
    bool ClientBomb::hasExploded() {
        return m_hasExploded;
    }

}

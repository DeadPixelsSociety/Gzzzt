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
        m_shape.setRadius(30);
        m_shape.setFillColor(sf::Color::Red);
        m_pos = {128., 128.};
    }

    ClientPlayer::ClientPlayer(const ClientPlayer& other)
    : m_name(other.getName()),
    m_id(other.getID()),
    m_pos(other.getPos()),
    m_shape(other.getShape()) {
    }

    ClientPlayer::~ClientPlayer() {
    }

    std::string ClientPlayer::getName() const {
        return m_name;
    }

    uint8_t ClientPlayer::getID() const {
        return m_id;
    }

    sf::Vector2f ClientPlayer::getPos() const {
        return m_pos;
    }

    sf::CircleShape ClientPlayer::getShape() const {
        return m_shape;
    }

    void ClientPlayer::setPos(const sf::Vector2f& pos) {
        m_pos = pos;
    }

    void ClientPlayer::update(float dt) {
        m_shape.setPosition(m_pos);
    }

    void ClientPlayer::render(sf::RenderWindow& window) {
        window.draw(m_shape);
    }

}

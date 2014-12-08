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
#ifndef GZZZT_CLIENT_PLAYER_H
#define GZZZT_CLIENT_PLAYER_H

#include <cstdint>
#include <string>

#include <gzzzt/client/ClientEntity.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace gzzzt {

    class ClientPlayer : public ClientEntity {
    public:
        explicit ClientPlayer(std::string name, uint8_t id);
        ClientPlayer(const ClientPlayer& other);
        virtual ~ClientPlayer();

        std::string getName() const;
        uint8_t getID() const;
        sf::CircleShape getShape() const;
        sf::Vector2f getPos() const;
        
        void setPos(const sf::Vector2f& pos);

        virtual void update(float dt) override;
        virtual void render(sf::RenderWindow& window) override;

    private:
        std::string m_name;
        uint8_t m_id;
        sf::Vector2f m_pos;
        sf::CircleShape m_shape;
    };

}


#endif // GZZZT_CLIENT_PLAYER_H

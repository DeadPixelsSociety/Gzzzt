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
#ifndef GZZZT_SERVER_PLAYER_H
#define GZZZT_SERVER_PLAYER_H

#include <string>

#include <SFML/Network.hpp>

#include <gzzzt/server/ServerEntity.h>

namespace gzzzt {

    class ServerPlayer : public ServerEntity {
    public:
        explicit ServerPlayer(sf::TcpSocket* socket);

        sf::TcpSocket* getTCPSocket() const;
        sf::IpAddress getAddress() const;
        unsigned short getPort() const;
        std::string getName() const;
        const char* toString();

        void setName(std::string name);

        virtual void update(float dt) override;

    private:
        sf::TcpSocket* m_TCPSocket;
        sf::IpAddress m_address;
        unsigned short m_port;
        std::string m_name;
    };

}

#endif // GZZZT_SERVER_PLAYER_H

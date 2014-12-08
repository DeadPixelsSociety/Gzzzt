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

#include <cstdint>
#include <string>

#include <SFML/Network.hpp>

#include <gzzzt/server/ServerEntity.h>
#include <gzzzt/server/Physics.h>

namespace gzzzt {

    class ServerPlayer : public ServerEntity {
    public:
        explicit ServerPlayer(sf::TcpSocket* socket);
        virtual ~ServerPlayer();

        sf::TcpSocket* getTCPSocket() const;
        sf::IpAddress getAddress() const;
        unsigned short getTCPPort() const;
        unsigned short getUDPPort() const;
        std::string getName() const;
        uint8_t getID() const;
        std::string toString() const;
        Body* getBody() const;

        void setName(std::string name);
        void setID(uint8_t id);
        void setUDPPort(unsigned short port);
        void closeTCPSocket();

        virtual void update(float dt) override;

    private:
        sf::TcpSocket* m_TCPSocket;
        sf::IpAddress m_address;
        unsigned short m_TCPPort;
        unsigned short m_UDPPort;
        std::string m_name;
        uint8_t m_id;
        Body* m_body;
    };

}

#endif // GZZZT_SERVER_PLAYER_H

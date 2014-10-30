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
#include <sstream>

#include <gzzzt/server/ServerPlayer.h>

namespace gzzzt {

    ServerPlayer::ServerPlayer(sf::TcpSocket* socket)
    : m_TCPSocket(socket),
    m_address(socket->getRemoteAddress()),
    m_port(socket->getRemotePort()) {
    }

    sf::TcpSocket* ServerPlayer::getTCPSocket() const {
        return m_TCPSocket;
    }

    sf::IpAddress ServerPlayer::getAddress() const {
        return m_address;
    }

    unsigned short ServerPlayer::getPort() const {
        return m_port;
    }

    std::string ServerPlayer::getName() const {
        return m_name;
    }

    void ServerPlayer::setName(std::string name) {
        m_name = name;
    }

    std::string ServerPlayer::toString() {
        std::ostringstream oss;
        bool nameDefined = m_name.length() > 0;
        if (nameDefined) {
            oss << m_name << "@[";
        }
        oss << m_address.toString() << ":" << m_port;
        if (nameDefined) {
            oss << "]";
        }
        return oss.str();
    }

    void ServerPlayer::update(float dt) {
        // TODO
    }
}

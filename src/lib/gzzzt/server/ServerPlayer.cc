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
    m_TCPPort(socket->getRemotePort()) {
        m_body = new Body();
        m_body->type = Body::Type::DYNAMIC;
        m_body->shape.kind = Shape::CIRCLE;
        m_body->shape.circle.radius = 30;
        m_body->pos = {64., 64.};
        m_body->velocity = {0., 0.};
    }

    ServerPlayer::~ServerPlayer() {
        delete m_body;
    }

    sf::TcpSocket* ServerPlayer::getTCPSocket() const {
        return m_TCPSocket;
    }

    sf::IpAddress ServerPlayer::getAddress() const {
        return m_address;
    }

    unsigned short ServerPlayer::getTCPPort() const {
        return m_TCPPort;
    }

    unsigned short ServerPlayer::getUDPPort() const {
        return m_UDPPort;
    }

    std::string ServerPlayer::getName() const {
        return m_name;
    }

    uint8_t ServerPlayer::getID() const {
        return m_id;
    }

    Body* ServerPlayer::getBody() const {
        return m_body;
    }

    uint8_t ServerPlayer::getBombs() const {
        return m_bombs;
    }

    void ServerPlayer::setName(std::string name) {
        m_name = name;
    }

    void ServerPlayer::setID(uint8_t id) {
        m_id = id;
    }

    void ServerPlayer::setUDPPort(unsigned short port) {
        m_UDPPort = port;
    }

    void ServerPlayer::closeTCPSocket() {
        delete m_TCPSocket;
        m_TCPSocket = nullptr;
    }

    void ServerPlayer::dropBomb() {
        m_bombs--;
    }

    std::string ServerPlayer::toString() const {
        std::ostringstream oss;
        bool nameDefined = m_name.length() > 0;
        if (nameDefined) {
            oss << m_name << "@[";
        }
        oss << m_address.toString() << ":" << m_TCPPort;
        if (nameDefined) {
            oss << "]";
        }
        return oss.str();
    }

    void ServerPlayer::update(float dt) {
        // TODO
    }
}

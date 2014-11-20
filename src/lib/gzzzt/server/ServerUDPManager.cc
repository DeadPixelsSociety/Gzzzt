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
#include <cassert>
#include <csignal>
#include <iostream>

#include <gzzzt/server/ServerUDPManager.h>
#include <gzzzt/shared/IdentifyRequest.h>

namespace gzzzt {

    static void signal_handler(int sig) {
        assert(sig == SIGINT || sig == SIGTERM);
        exit(1);
    }

    ServerUDPManager::ServerUDPManager(unsigned short port)
    : m_port(port) {
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
    }

    ServerUDPManager::~ServerUDPManager() {
        close();
    }

    bool ServerUDPManager::init() {
        return m_socket.bind(m_port) == sf::Socket::Done;
    }

    void ServerUDPManager::close() {
        m_socket.unbind();
    }

    bool ServerUDPManager::broadcast(const gzzzt::ServerPlayerList& players, const gzzzt::Response& resp) {
        std::vector<uint8_t> bytes = resp.serialize();
        for (auto player : players) {
            if (!m_socket.send(&bytes[0], bytes.size(), player->getAddress(), player->getUDPPort()) != sf::Socket::Done) {
                return false;
            }
        }
        return true;
    }

    bool ServerUDPManager::send(const gzzzt::ServerPlayer& player, const gzzzt::Response& resp) {
        std::vector<uint8_t> bytes = resp.serialize();
        return m_socket.send(&bytes[0], bytes.size(), player.getAddress(), player.getUDPPort()) == sf::Socket::Done;
    }

    gzzzt::Request* ServerUDPManager::receive() {
        std::vector<uint8_t> bytes(64);
        std::size_t bytesRecv;
        sf::IpAddress senderAddress;
        unsigned short senderPort;
        if (m_socket.receive(&bytes[0], bytes.size(), bytesRecv, senderAddress, senderPort) != sf::Socket::Done) {
            return nullptr;
        }
        gzzzt::Request* req = nullptr;
        gzzzt::RequestType reqType = gzzzt::Request::getType(bytes);
        switch (reqType) {
            case gzzzt::RequestType::ACTION:
                req = new ActionRequest(bytes);
                break;
            case gzzzt::RequestType::IDENTIFY:
                req = new IdentifyRequest(bytes);
                break;
            default: // Error
                return nullptr;
        }
        return req;
    }

    bool ServerUDPManager::receiveIdentifyRequest(gzzzt::ServerPlayerList& players) {
        std::vector<uint8_t> bytes(64);
        std::size_t bytesRecv;
        sf::IpAddress senderAddress;
        unsigned short senderPort;
        if (m_socket.receive(&bytes[0], bytes.size(), bytesRecv, senderAddress, senderPort) != sf::Socket::Done) {
            return false;
        }
        gzzzt::RequestType reqType = gzzzt::Request::getType(bytes);
        if (reqType != gzzzt::RequestType::IDENTIFY) {
            return false;
        }
        gzzzt::IdentifyRequest idReq(bytes);
        gzzzt::ServerPlayer* player = players.getById(idReq.getPlayerId());
        if (player == nullptr) {
            return false;
        }
        player->setUDPPort(senderPort);
        return true;
    }
}

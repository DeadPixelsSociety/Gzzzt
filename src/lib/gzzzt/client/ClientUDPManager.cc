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

#include <gzzzt/client/ClientUDPManager.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/GameStateResponse.h>
#include <gzzzt/shared/NewPlayerResponse.h>
#include <gzzzt/shared/StartGameResponse.h>

namespace gzzzt {

    static void signal_handler(int sig) {
        assert(sig == SIGINT || sig == SIGTERM);
        exit(1);
    }

    ClientUDPManager::ClientUDPManager(const std::string& address, unsigned short port)
    : m_address(address),
    m_port(port) {
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
        m_socket.setBlocking(false);
    }

    ClientUDPManager::~ClientUDPManager() {
    }

    bool ClientUDPManager::send(const gzzzt::Request& req) {
        std::vector<uint8_t> bytes = req.serialize();
        return m_socket.send(&bytes[0], bytes.size(), m_address, m_port) == sf::Socket::Done;
    }

    gzzzt::Response* ClientUDPManager::receive() {
        std::vector<uint8_t> bytes(64);
        std::size_t bytesRecv;
        sf::IpAddress senderAddress;
        unsigned short senderPort;
        if (m_socket.receive(&bytes[0], bytes.size(), bytesRecv, senderAddress, senderPort) != sf::Socket::Done) {
            return nullptr;
        }
        if (senderAddress != m_address || senderPort != m_port) {
            // The server did not send this message
            return nullptr;
        }
        bytes.resize(bytesRecv);
        gzzzt::Response* resp = nullptr;
        gzzzt::ResponseType respType = gzzzt::Response::getType(bytes);
        switch (respType) {
            case gzzzt::ResponseType::ERROR:
                resp = new gzzzt::ErrorResponse(bytes);
                break;
            case gzzzt::ResponseType::NEW_PLAYER_OK:
                resp = new gzzzt::NewPlayerResponse(bytes);
                break;
            case gzzzt::ResponseType::START_GAME:
                resp = new gzzzt::StartGameResponse(bytes);
                break;
            case gzzzt::ResponseType::GAME_STATE:
                resp = new gzzzt::GameStateResponse(bytes);
                break;
            default:
                return nullptr;
        }
        return resp;
    }
}

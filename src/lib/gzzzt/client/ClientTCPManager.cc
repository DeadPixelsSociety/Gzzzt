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
#include <map>

#include <gzzzt/client/ClientTCPManager.h>

namespace gzzzt {

    ClientTCPManager::ClientTCPManager(std::string serverAddress, unsigned short serverPort)
    : m_serverAddress(serverAddress),
    m_serverPort(serverPort) {
    }

    std::string ClientTCPManager::getServerAddress() const {
        return m_serverAddress;
    }

    unsigned short ClientTCPManager::getServerPort() const {
        return m_serverPort;
    }

    bool ClientTCPManager::connect() {
        return m_socket.connect(m_serverAddress, m_serverPort) == sf::Socket::Done;
    }

    void ClientTCPManager::disconnect() {
        m_socket.disconnect();
    }

    bool ClientTCPManager::send(const gzzzt::Request& req) {
        std::vector<uint8_t> bytes = req.serialize();
        return m_socket.send(&bytes[0], bytes.size()) == sf::Socket::Done;
    }

    gzzzt::Response* ClientTCPManager::receive() {
        std::vector<uint8_t> bytes;
        bytes.assign(64, 0);
        std::size_t bytesRecv;
        if (m_socket.receive(&bytes[0], bytes.size(), bytesRecv) != sf::Socket::Done) {
            return nullptr;
        }
        bytes.resize(bytesRecv);
        gzzzt::ResponseType respType = gzzzt::Response::getType(bytes);
        gzzzt::Response* resp = nullptr;
        switch (respType) {
            case ResponseType::ERROR:
                resp = new gzzzt::ErrorResponse(bytes);
                break;
            case ResponseType::NEW_PLAYER_OK:
                resp = new gzzzt::NewPlayerResponse(bytes);
                break;
            case ResponseType::START_GAME:
                resp = new gzzzt::StartGameResponse(bytes);
                break;
            case ResponseType::GAME_STATE:
                resp = new gzzzt::GameStateResponse(bytes);
                break;
        }
        return resp;
    }

    bool ClientTCPManager::declareAsNewPlayer(const std::string& name, std::string& error) {
        if (!send(gzzzt::NewPlayerRequest(name))) {
            error = "Could not send data to server";
            return false;
        }
        gzzzt::Response* resp = receive();
        if (resp == nullptr) {
            error = "Could not receive data from server";
            return false;
        }
        if (resp->getRespType() == gzzzt::ResponseType::ERROR) {
            error = dynamic_cast<gzzzt::ErrorResponse*> (resp)->getReason();
            return false;
        }
        delete resp;
        return true;
    }

    bool ClientTCPManager::receiveGameData(std::list<gzzzt::ClientPlayer>& players, unsigned short& serverPortUDP, std::string& error) {
        gzzzt::Response* resp = receive();
        if (resp == nullptr) {
            error = "Could not receive data from server";
            return false;
        }
        if (resp->getRespType() == gzzzt::ResponseType::ERROR) {
            error = dynamic_cast<gzzzt::ErrorResponse*> (resp)->getReason();
            return false;
        }
        gzzzt::StartGameResponse startGameResp = *(dynamic_cast<gzzzt::StartGameResponse*>(resp));
        std::map<uint8_t, std::string> playersData = startGameResp.getPlayers();
        for (auto p : playersData) {
            players.push_back(gzzzt::ClientPlayer(p.second, p.first));
        }
        serverPortUDP = startGameResp.getServerPortUDP();
        delete resp;
        return true;
    }
}

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

#include <gzzzt/server/ServerTCPManager.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/NewPlayerResponse.h>
#include <gzzzt/shared/NewPlayerRequest.h>

namespace gzzzt {

    static void signal_exit(int sig) {
        assert(sig == SIGINT || sig == SIGTERM);
        exit(1);
    }

    ServerTCPManager::ServerTCPManager(unsigned short port) : m_port(port) {
        std::signal(SIGINT, signal_exit);
        std::signal(SIGTERM, signal_exit);
    }

    bool ServerTCPManager::init() {
        if (m_listener.listen(m_port) != sf::Socket::Done) {
            return false;
        }
        m_selector.add(m_listener);
        return true;
    }

    void ServerTCPManager::close() {
        m_selector.clear();
        m_listener.close();
    }

    bool ServerTCPManager::waitPlayers(int nbPlayersToWait, gzzzt::ServerPlayerList& players) {
        assert(nbPlayersToWait > 0);
        uint8_t nbPlayersRegistered = 0;
        while (nbPlayersRegistered < nbPlayersToWait) {
            if (m_selector.wait()) {
                sf::TcpSocket* playerSocket;
                if (m_selector.isReady(m_listener)) {
                    // New pending connection
                    playerSocket = new sf::TcpSocket;
                    if (m_listener.accept(*playerSocket) != sf::Socket::Done) {
                        std::cout << "Could not accept connection" << std::endl;
                        delete playerSocket;
                    } else {
                        playerSocket->setBlocking(false);
                        m_selector.add(*playerSocket);
                        gzzzt::ServerPlayer* player = new gzzzt::ServerPlayer(playerSocket);
                        players.add(player);
                        std::cout << "New connection from " << player->toString() << std::endl;
                    }
                } else {
                    // Find the client's socket which is ready
                    auto it = players.begin();
                    while (!m_selector.isReady(*((*it)->getTCPSocket()))) {
                        it++;
                    }
                    gzzzt::ServerPlayer* player = *it;
                    sf::TcpSocket* playerSocket = player->getTCPSocket();
                    gzzzt::NewPlayerRequest* playerReq;
                    std::vector<uint8_t> bytes(64);
                    std::size_t nbBytesRead;
                    sf::Socket::Status state = playerSocket->receive(&bytes[0], bytes.size(), nbBytesRead);
                    bytes.resize(nbBytesRead);
                    switch (state) {
                        case sf::Socket::Status::Done:
                            playerReq = new gzzzt::NewPlayerRequest(bytes);
                            if (isDuplicatedName(players, playerReq->getPlayerName())) {
                                std::cout << "Name \"" << playerReq->getPlayerName() << "\" already taken. " << player->toString() << " needs to choose another one" << std::endl;
                                // Send an error to the client 
                                bytes = gzzzt::ErrorResponse("Name already taken").serialize();
                                playerSocket->send(&bytes[0], bytes.size());
                            } else {
                                player->setName(playerReq->getPlayerName());
                                player->setID(nbPlayersRegistered); // Use the nb of players registered as id
                                nbPlayersRegistered++;
                                std::cout << "Client chose a name : " << player->toString() << std::endl;
                                bytes = gzzzt::NewPlayerResponse().serialize();
                                playerSocket->send(&bytes[0], bytes.size());
                            }
                            delete playerReq;
                            break;
                        case sf::Socket::Status::Disconnected:
                            std::cout << "Client %s is disconnected" << player->toString() << std::endl;
                            m_selector.remove(*playerSocket);
                            playerSocket->disconnect();
                            delete playerSocket;
                            players.remove(*it);
                            break;
                        case sf::Socket::Status::NotReady:
                            std::cout << "The socket is not ready" << std::endl;
                            return false;
                        case sf::Socket::Status::Error:
                            std::cout << "Error while receiving data" << std::endl;
                            return false;
                    }
                }
            }
        }
        return true;
    }

    bool ServerTCPManager::broadcast(gzzzt::ServerPlayerList& players, const gzzzt::Response& msg) const {
        std::vector<uint8_t> bytes = msg.serialize();
        for (auto player : players) {
            if (player->getTCPSocket()->send(&bytes[0], bytes.size()) != sf::Socket::Done) {
                return false;
            }
        }
        return true;
    }

    bool ServerTCPManager::isDuplicatedName(const gzzzt::ServerPlayerList& players, const std::string& name) const {
        for (auto player : players) {
            if (player->getName().compare(name) == 0) {
                return true;
            }
        }
        return false;
    }

}

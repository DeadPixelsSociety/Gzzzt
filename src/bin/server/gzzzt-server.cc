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
#include <atomic>
#include <cassert>
#include <csignal>
#include <iostream>
#include <set>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <gzzzt/server/Game.h>
#include <gzzzt/server/ServerPlayer.h>
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/NewPlayerResponse.h>

#include "config.h"

static std::atomic_bool should_continue
{
    true
};

static void help(void) {
    std::cout << "Usage: gzzzt-server <PORT>" << std::endl;
}

static bool isDuplicatedName(const std::vector<gzzzt::ServerPlayer>& players, const std::string& name) {
    for (auto player : players) {
        if (player.getName().compare(name) == 0) {
            return true;
        }
    }
    return false;
}

static void signal_handler(int sig) {
    assert(sig == SIGINT || sig == SIGTERM);
    should_continue = false;
}

//static void receiveMsg(const sf::UdpSocket& socket) {
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the receiving thread...\n");
//    while (should_continue) {
//        // TODO:
//    }
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the receiving thread...\n");
//}
//
//static void broadcastMsg(const sf::UdpSocket& socket) {
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the broadcasting thread...\n");
//    while (should_continue) {
//        // TODO:
//    }
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the broadcasting thread...\n");
//}

int main(int argc, char** argv) {
    if (argc != 2) {
        help();
        return 1;
    }
    gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the server...\n");
    gzzzt::Log::info(gzzzt::Log::GENERAL, "You can stop it with CTRL+C or with the kill command.\n");

    // set signal handlers
    auto previous_sigint_handler = std::signal(SIGINT, signal_handler);
    if (previous_sigint_handler == SIG_ERR) {
        gzzzt::Log::error(gzzzt::Log::GENERAL, "Could not set the signal handler for SIGINT\n");
        return 2;
    }

    auto previous_sigterm_handler = std::signal(SIGTERM, signal_handler);
    if (previous_sigterm_handler == SIG_ERR) {
        gzzzt::Log::error(gzzzt::Log::GENERAL, "Could not set the signal handler for SIGTERM\n");
        return 2;
    }

    unsigned short port = std::strtoul(argv[1], nullptr, 10);
    sf::SocketSelector selector;

    // initialize the listener
    sf::TcpListener tcpListener;
    if (tcpListener.listen(port) != sf::Socket::Done) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not bind listener on port %d\n", port);
        return 3;
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Waiting for connections on port %d...\n", port);
    selector.add(tcpListener);

    // wait for players
    std::vector<gzzzt::ServerPlayer> players;
    while (should_continue) {
        if (selector.wait()) {
            sf::TcpSocket* playerSocket;
            if (selector.isReady(tcpListener)) {
                // New pending connection
                playerSocket = new sf::TcpSocket;
                if (tcpListener.accept(*playerSocket) != sf::Socket::Done) {
                    gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not accept connection\n");
                    delete playerSocket;
                } else {
                    playerSocket->setBlocking(false);
                    selector.add(*playerSocket);
                    gzzzt::ServerPlayer player(playerSocket);
                    players.push_back(player);
                    gzzzt::Log::info(gzzzt::Log::NETWORK, "New connection from %s\n", player.toString().c_str());
                }
            } else {
                // Find the client's socket which is ready
                std::vector<gzzzt::ServerPlayer>::iterator it = players.begin();
                while (!selector.isReady(*(it->getTCPSocket()))) {
                    it++;
                }
                gzzzt::ServerPlayer& player = *it;
                sf::TcpSocket* playerSocket = player.getTCPSocket();
                gzzzt::RequestType reqType;
                gzzzt::NewPlayerRequest* playerReq;
                std::vector<uint8_t> bytes(64);
                std::size_t nbBytesRead;
                sf::Socket::Status state = playerSocket->receive(&bytes[0], bytes.size(), nbBytesRead);
                bytes.resize(nbBytesRead);
                switch (state) {
                    case sf::Socket::Status::Done:
                        reqType = gzzzt::Request::getType(bytes);
                        if (reqType != gzzzt::RequestType::NEW_PLAYER) {
                            gzzzt::Log::error(gzzzt::Log::NETWORK, "Bad type of message from %s\n", player.toString().c_str());
                            break;
                        }
                        playerReq = new gzzzt::NewPlayerRequest(&bytes);
                        if (isDuplicatedName(players, playerReq->getPlayerName())) {
                            gzzzt::Log::info(gzzzt::Log::NETWORK,
                                    "Name \"%s\" already taken. %s needs to choose another one\n",
                                    playerReq->getPlayerName().c_str(),
                                    player.toString().c_str());
                            // Send an error to the client 
                            gzzzt::ErrorResponse("Name already taken").serialize(&bytes);
                            playerSocket->send(&bytes[0], bytes.size());
                        } else {
                            player.setName(playerReq->getPlayerName());
                            gzzzt::Log::info(gzzzt::Log::NETWORK, "Client chose a name : %s\n", player.toString().c_str());
                            gzzzt::NewPlayerResponse().serialize(&bytes);
                            playerSocket->send(&bytes[0], bytes.size());
                        }
                        delete playerReq;
                        break;
                    case sf::Socket::Status::Disconnected:
                        gzzzt::Log::info(gzzzt::Log::NETWORK, "Client %s is disconnected\n", player.toString().c_str());
                        selector.remove(*playerSocket);
                        delete playerSocket;
                        players.erase(it);
                        break;
                    case sf::Socket::Status::NotReady:
                        gzzzt::Log::error(gzzzt::Log::NETWORK, "The socket is not ready\n");
                        break;
                    case sf::Socket::Status::Error:
                        gzzzt::Log::error(gzzzt::Log::NETWORK, "Error while receiving date\n");
                        break;
                }
            }
        }
    }
    tcpListener.close();


    // close the TCP listener and initialize the UDP sockets
    //    tcpSocket.disconnect();
    //    sf::UdpSocket udpSocket;
    //    if (udpSocket.bind(port) != sf::Socket::Done) {
    //        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not bind socket to port %d\n", port);
    //        return 1;
    //    }
    //
    //    // launch the threads
    //    sf::Thread receiver(&receiveMsg, std::ref(udpSocket));
    //    sf::Thread broadcaster(&broadcastMsg, std::ref(udpSocket));
    //    receiver.launch();
    //    broadcaster.launch();

    // initialize
    gzzzt::Game game;

    // load resources


    // add entities


    // main loop
    sf::Clock clock;

    while (should_continue) {
        // input (network)

        // update
        sf::Time elapsed = clock.restart();
        game.update(elapsed.asSeconds());
    }

    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the server...\n");

    //    receiver.wait();
    //    broadcaster.wait();
    return 0;
}

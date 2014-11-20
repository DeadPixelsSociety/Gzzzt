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
#include <gzzzt/server/ServerPlayerList.h>
#include <gzzzt/server/ServerTCPManager.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/IdentifyRequest.h>
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/NewPlayerResponse.h>
#include <gzzzt/shared/StartGameResponse.h>

#include "config.h"

static std::atomic_bool should_continue
{
    true
};

static void help(void) {
    std::cout << "Usage: gzzzt-server <TCP_PORT> <UDP_PORT>" << std::endl;
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
    if (argc != 3) {
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
    unsigned short udpPort = std::strtoul(argv[2], nullptr, 10);
    
    // Init the TCP manager
    gzzzt::ServerTCPManager tcpManager(port);
    if (!tcpManager.init()) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not init TCP connection\n");
        return 3;
    }
    
    // Wait for the players
    gzzzt::ServerPlayerList players;
    if (!tcpManager.waitPlayers(2, players)) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Error while waiting for players\n");
        return 4;
    }

    // Broadcast the players list
    std::map<uint8_t, std::string> playersData;
    for (auto player : players) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "-> %s(%d)\n", player->getName().c_str(), player->getID());
        playersData.insert(std::pair<uint8_t, std::string>(player->getID(), player->getName()));
    }
    if (!tcpManager.broadcast(players, gzzzt::StartGameResponse(playersData, udpPort))) {
        gzzzt::Log::fatal(gzzzt::Log::NETWORK, "Error while broadcasting to the players\n");
    }

    // Initialize the UDP sockets
//    sf::UdpSocket udpSocket;
//    if (udpSocket.bind(udpPort) != sf::Socket::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not bind UDP socket to port %d\n", port);
//        return 4;
//    }
//    gzzzt::Log::info(gzzzt::Log::NETWORK, "UDP socket created\n");
//    std::size_t received;
//    sf::IpAddress sender;
//    unsigned short senderPort;
//    selector.add(udpSocket);
//    udpSocket.setBlocking(false);
//    bytes.assign(64, 0);
//    while (should_continue) {
//        if (selector.wait()) {
//            if (selector.isReady(udpSocket)) {
//                if (udpSocket.receive(&bytes[0], bytes.size(), received, sender, senderPort) != sf::Socket::Status::Done) {
//                    gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not receive data\n");
//                    return 5;
//                }
//                uint8_t id = gzzzt::IdentifyRequest(bytes).getID();
//                gzzzt::ServerPlayer* player = players.getById(id);
//                player->setUDPPort(senderPort);
//                gzzzt::Log::info(gzzzt::Log::NETWORK, "%s(%d) is on port %d\n", player->getName().c_str(), id, senderPort);
//
//                // TODO: remove this
//                // Send response
//                if (udpSocket.send(player->getName().data(), player->getName().size(), player->getAddress(), senderPort) != sf::Socket::Status::Done) {
//                    gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not send data\n");
//                    return 5;
//                }
//            }
//        }
//        bytes.assign(64, 0);
//    }
//    udpSocket.unbind();

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

//    tcpListener.close();
    tcpManager.close();
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the server...\n");

    //    receiver.wait();
    //    broadcaster.wait();
    return 0;
}

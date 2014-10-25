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
#include <functional>
#include <iostream>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <gzzzt/server/Game.h>
#include <gzzzt/shared/Log.h>

#include "config.h"

static std::atomic_bool should_continue {true};

static void help(void) {
    std::cout << "Usage: gzzzt-server <PORT>" << std::endl;
    std::cout << "Example: gzzzt-server 5000" << std::endl;
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

    // initialize the TCP socket
    sf::TcpListener tcpListener;
    if (tcpListener.listen(port) != sf::Socket::Done) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not bind listener on port %d\n", port);
        return 3;
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Waiting for connections on port %d...\n", port);
    
    // wait for 1 player
    short nbPlayers = 0;
    sf::TcpSocket playerSocket;
    while (nbPlayers < 2) {
        if (tcpListener.accept(playerSocket) != sf::Socket::Done) {
            gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not accept connection\n");
            return 4;
        }
        unsigned short playerPort = playerSocket.getRemotePort();
        sf::IpAddress playerAddress = playerSocket.getRemoteAddress();
        nbPlayers++;
        // TODO: update list of players
        gzzzt::Log::info(gzzzt::Log::NETWORK, "New connection from \"%s:%d\"\n", playerAddress.toString().c_str(), playerPort);
    }
    playerSocket.disconnect();
    tcpListener.close();
    
    //    // wait for 1 player
    //    sf::TcpSocket tcpSocket;
    //    short nbPlayers = 0;
    //    while (nbPlayers < 1) {
    //        if (tcpListener.accept(tcpSocket) != sf::Socket::Done) {
    //            gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not accept socket\n");
    //            return 1;
    //        }
    //        nbPlayers++;
    //        // TODO: create players
    //        gzzzt::Log::info(gzzzt::Log::NETWORK, "New connection from \"%s:%d\"\n", tcpSocket.getRemoteAddress(), tcpSocket.getRemotePort());
    //    }

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

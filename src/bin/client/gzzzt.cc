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
#include <iostream>
#include <cstdlib>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <gzzzt/client/World.h>
#include <gzzzt/shared/Action.h>
#include <gzzzt/shared/Log.h>

#include "config.h"

static void help(void) {
    std::cout << "Usage: gzzzt <PLAYER_NAME> <SERVER_ADDRESS:PORT>" << std::endl;
    std::cout << "Example: gzzzt robot1 192.168.1.56:5000 6000" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        help();
        return 1;
    }
    gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
    std::string playerName(argv[1]);
    std::string serverURL(argv[2]);
    std::size_t pos = serverURL.find(":");
    if (pos == std::string::npos) {
        std::cout << "Error: bad address format" << std::endl;
        help();
        return 2;
    }
    std::string serverAddress = serverURL.substr(0, pos);
    unsigned short serverPort = std::strtoul(serverURL.substr(pos + 1).c_str(), nullptr, 10);
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Connecting to %s on port %d...\n", serverAddress.c_str(), serverPort);
    sf::TcpSocket tcpSocket;
    if (tcpSocket.connect("127.0.0.1", serverPort) != sf::Socket::Done) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not connect to %s on port %d\n", serverAddress.c_str(), serverPort);
        return 3;
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Connected to %s on port %d...\n", serverAddress.c_str(), serverPort);
    
    // TODO: send request with player's name


    //    sf::IpAddress server("127.0.0.1");
    //    sf::UdpSocket socket;
    //    gzzzt::Action msg(gzzzt::ActionType::DROP_BOMB);
    //    std::vector<uint8_t> bytes;
    //    unsigned short port = 2048;
    //    if (msg.serialize(&bytes) == nullptr) {
    //        return 2;
    //    }
    //    unsigned char* rawData = bytes.data();
    //    if (socket.send(rawData, sizeof(rawData), server, port) != sf::Socket::Done) {
    //        return 3;
    //    }
    //    gzzzt::Log::info(gzzzt::Log::GENERAL, "Message sent!\n");

    // initialize
    gzzzt::World world;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Gzzzt (version " GAME_VERSION ")");
    window.setKeyRepeatEnabled(false);

    // load resources


    // add entities


    // main loop
    sf::Clock clock;

    while (window.isOpen()) {
        // input
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    default:
                        break;
                }

            }
        }

        // update
        sf::Time elapsed = clock.restart();
        world.update(elapsed.asSeconds());

        // render
        window.clear(sf::Color::White);
        world.render(window);
        window.display();
    }

    return 0;
}

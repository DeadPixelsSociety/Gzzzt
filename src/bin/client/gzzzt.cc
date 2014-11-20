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
#include <list>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <gzzzt/client/ClientPlayer.h>
#include <gzzzt/client/ClientTCPManager.h>
#include <gzzzt/client/World.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/IdentifyRequest.h>
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/StartGameResponse.h>

#include "config.h"

static void help(void) {
    std::cout << "Usage: gzzzt <PLAYER_NAME> <SERVER_ADDRESS:PORT>" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        help();
        return 1;
    }
    gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
    std::string playerName(argv[1]);
    std::string serverURL(argv[2]);
    std::size_t pos = serverURL.find(":");
    if (pos == std::string::npos) {
        gzzzt::Log::error(gzzzt::Log::GENERAL, "Bad address format\n");
        help();
        return 2;
    }
    std::string serverAddress = serverURL.substr(0, pos);
    unsigned short serverPortTCP = std::strtoul(serverURL.substr(pos + 1).c_str(), nullptr, 10);
    gzzzt::ClientTCPManager tcpManager(serverAddress, serverPortTCP);
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Connecting to %s on port %d...\n", serverAddress.c_str(), serverPortTCP);
    std::string error;
    if (!tcpManager.connect()) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not connect to %s on port %d\n", serverAddress.c_str(), serverPortTCP);
        return 3;
    }
    
    // Send a request to be a player
    if (!tcpManager.declareAsNewPlayer(playerName, error)) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "%s\n", error.c_str());
        tcpManager.disconnect();
        return 3;
    }
    
//    // Send a request to be a player
//    if (!tcpManager.send(gzzzt::NewPlayerRequest(playerName))) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not send request to server\n");
//        tcpManager.disconnect();
//        return 4;
//    }
//    
//    // Wait for the response
//    gzzzt::Response resp;
//    if (!tcpManager.receive(resp)) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not receive data to server\n");
//        tcpManager.disconnect();
//        return 5;
//    }
//    if (resp.getRespType() == gzzzt::ResponseType::ERROR) {
//        gzzzt::ErrorResponse err = static_cast<gzzzt::ErrorResponse>(resp);
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Response: Error: %s\n", err.getReason().c_str());
//        tcpManager.disconnect();
//        return 6;
//    }
    
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Name accepted.\n");
    
//    gzzzt::NewPlayerRequest playerReq(playerName);
//    std::vector<uint8_t> bytes = playerReq.serialize();
//    gzzzt::Log::info(gzzzt::Log::NETWORK, "Connected to \"%s:%d\" using port %d...\n", serverAddress.c_str(), serverPortTCP, tcpSocket.getLocalPort());
//    if (tcpSocket.send(&bytes[0], bytes.size()) != sf::Socket::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not send data to server\n");
//        tcpSocket.disconnect();
//        return 5;
//    }
//    gzzzt::Log::info(gzzzt::Log::NETWORK, "Waiting for the response...\n");
//
//    // Wait for the response
//    std::size_t nbBytesRead;
//    bytes.assign(64, 0);
//    if (tcpSocket.receive(&bytes[0], bytes.size(), nbBytesRead) != sf::Socket::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not received the server's response\n");
//        tcpSocket.disconnect();
//        return 6;
//    }
//    bytes.resize(nbBytesRead);
//    gzzzt::ResponseType respType = gzzzt::Response::getType(bytes);
//    if (respType == gzzzt::ResponseType::ERROR) {
//        gzzzt::ErrorResponse err(bytes);
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Response: Error: %s\n", err.getReason().c_str());
//        tcpSocket.disconnect();
//        return 7;
//    }
//    gzzzt::Log::info(gzzzt::Log::NETWORK, "Name accepted.\n");

    std::list<gzzzt::ClientPlayer> players;
    if (!tcpManager.receivePlayers(players, error)) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "%s\n", error.c_str());
        tcpManager.disconnect();
        return 3;
    }
    
    
    
    // Wait for the players list
//    std::vector<gzzzt::ClientPlayer> players;
//    bytes.assign(64, 0);
//    if (tcpSocket.receive(&bytes[0], bytes.size(), nbBytesRead) != sf::Socket::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not received the server's msg\n");
//        tcpSocket.disconnect();
//        return 6;
//    }
//    bytes.resize(nbBytesRead);
//    gzzzt::StartGameResponse resp(bytes);
//    std::map<uint8_t, std::string> playersData = resp.getPlayers();
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "List of players :\n");
//    uint8_t playerId = 0;
//    for (auto p : playersData) {
//        players.push_back(gzzzt::ClientPlayer(p.second, p.first));
//        gzzzt::Log::info(gzzzt::Log::GENERAL, "- %s (%d)\n", p.second.c_str(), p.first);
//        if (p.second.compare(playerName) == 0) {
//            playerId = p.first;
//        }
//    }
    
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the game...\n");

    // Initialize the UDP socket
//    unsigned short serverPortUDP = resp.getServerPortUDP();
//    sf::UdpSocket udpSocket;
//    bytes = gzzzt::IdentifyRequest(playerId).serialize();
//    if (udpSocket.send(&bytes[0], bytes.size(), serverAddress, serverPortUDP) != sf::Socket::Status::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not send data\n");
//        return 5;
//    }
//    bytes.assign(64, 0);
//    std::size_t sizeRecv;
//    sf::IpAddress tmp1;
//    if (udpSocket.receive(&bytes[0], bytes.size(), sizeRecv, tmp1, serverPortUDP) != sf::Socket::Status::Done) {
//        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not recv data\n");
//        return 5;
//    }
//    bytes.resize(sizeRecv);
//    gzzzt::Log::info(gzzzt::Log::GENERAL, "RECV : %d from %s, %d\n", sizeRecv, tmp1.toString().c_str(), serverPortUDP);

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
    tcpManager.disconnect();

    return 0;
}

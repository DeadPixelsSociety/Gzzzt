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
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <bitset>
#include <iostream>
#include <list>
#include <thread>

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <gzzzt/client/ClientBomb.h>
#include <gzzzt/client/ClientMap.h>
#include <gzzzt/client/ClientPlayer.h>
#include <gzzzt/client/ClientTCPManager.h>
#include <gzzzt/client/ClientUDPManager.h>
#include <gzzzt/shared/Resource.h>
#include <gzzzt/client/World.h>
#include <gzzzt/shared/ActionRequest.h>
#include <gzzzt/shared/ConcurrentQueue.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/IdentifyRequest.h>
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/StartGameResponse.h>

#include "config.h"
#include "gzzzt/client/SoundHandler.h"

static std::atomic_bool should_continue
{
    true
};

static void stopThreads() {
    should_continue = false;
}

static void signal_handler(int sig) {
    assert(sig == SIGINT || sig == SIGTERM);
    stopThreads();
}

static void help(void) {
    std::cout << "Usage: gzzzt <PLAYER_NAME> <SERVER_ADDRESS:PORT>" << std::endl;
}

static void receiveMsg(gzzzt::ClientUDPManager& udpManager, gzzzt::ConcurrentQueue<gzzzt::Response*>& inQueue) {
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the receiver thread...\n");
    gzzzt::Response* resp;
    while (should_continue) {
        resp = udpManager.receive();
        if (resp != nullptr) {
            inQueue.push(resp);
        }
    }
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the receiver thread...\n");
}

static sf::Vector2f getPos(uint8_t id, std::vector<float> values) {
    for (unsigned int i = 0; i < values.size(); i += 3) {
        if (id == static_cast<uint8_t> (values[i])) {
            return sf::Vector2f(values[i + 1], values[i + 2]);
        }
    }
    return sf::Vector2f(-1., -1.);
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

    // Create the TCP manager
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
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Name accepted.\n");

    // Receive the game's data (list of players + server UDP port)
    unsigned short serverPortUDP;
    std::list<gzzzt::ClientPlayer*> players;
    if (!tcpManager.receiveGameData(players, serverPortUDP, error)) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "%s\n", error.c_str());
        tcpManager.disconnect();
        return 3;
    }

    uint8_t playerId = 0;
    for (auto p : players) {
        gzzzt::Log::info(gzzzt::Log::GENERAL, "Player #%d : %s\n", p->getID(), p->getName().c_str());
        // Get current player's ID
        if (p->getName().compare(playerName) == 0) {
            playerId = p->getID();
        }
    }
    gzzzt::Log::info(gzzzt::Log::GENERAL, "My ID : %d\n", playerId);
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Server port UDP : %d\n", serverPortUDP);


    // Initialize the UDP socket
    gzzzt::ClientUDPManager udpManager(serverAddress, serverPortUDP);

    // Send a request to identify
    if (!udpManager.send(gzzzt::IdentifyRequest(playerId))) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not send data\n");
        tcpManager.disconnect();
        return 5;
    }

    // Create concurrent queue for the messages
    gzzzt::ConcurrentQueue<gzzzt::Response*> inQueue;
    // Launch the thread
    std::thread receiver(&receiveMsg, std::ref(udpManager), std::ref(inQueue));

    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the game...\n");

    // initialize
    gzzzt::World world;
    gzzzt::ClientMap* map;

    gzzzt::ResourceManager resourceManager;

    resourceManager.addSearchDir(GAME_DATADIR);
    resourceManager.addSearchDir("..");

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Gzzzt (version " GAME_VERSION ")");
    window.setKeyRepeatEnabled(false);

    // load resources

#if _DEBUG_
    map = new gzzzt::ClientMap("maps/simple/simple.tmx", resourceManager);
#else
    assert(true);
#endif

    // add entities
    world.addEntity(map);
    for (auto p : players) {
        world.addEntity(p);
    }

    // main loop
    sf::Clock clock;
    std::bitset<5> keys;
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
                    case sf::Keyboard::Up:
                        keys.set(MOVE_UP, true);
                        break;
                    case sf::Keyboard::Down:
                        keys.set(MOVE_DOWN, true);
                        break;
                    case sf::Keyboard::Left:
                        keys.set(MOVE_LEFT, true);
                        break;
                    case sf::Keyboard::Right:
                        keys.set(MOVE_RIGHT, true);
                        break;
                    case sf::Keyboard::Space:
                        keys.set(DROP_BOMB, true);
                        break;
                    default:
                        break;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        keys.set(MOVE_UP, false);
                        break;
                    case sf::Keyboard::Down:
                        keys.set(MOVE_DOWN, false);
                        break;
                    case sf::Keyboard::Left:
                        keys.set(MOVE_LEFT, false);
                        break;
                    case sf::Keyboard::Right:
                        keys.set(MOVE_RIGHT, false);
                        break;
                    case sf::Keyboard::Space:
                        keys.set(DROP_BOMB, false);
                        break;
                    default:
                        break;
                }
            }
            gzzzt::ActionRequest req(keys, playerId);
            if (udpManager.send(req)) {
                gzzzt::Log::debug(gzzzt::Log::GENERAL, "Request sent\n");
            } else {
                gzzzt::Log::error(gzzzt::Log::GENERAL, "Error while sending a request\n");
            }
        }

        gzzzt::Response* resp = nullptr;
        while (inQueue.tryPop(resp)) {
            // There is a pending message
            gzzzt::GameStateResponse* gameStateResp = dynamic_cast<gzzzt::GameStateResponse*> (resp);
            // TODO: refactor this !
            std::vector<float> playersPositions = gameStateResp->getPlayersPositions();
            std::vector<float> bombsPositions = gameStateResp->getBombsPositions();
            int nbBombs = bombsPositions.size() / 2;
            gzzzt::Log::debug(gzzzt::Log::GENERAL, "NB BOMB: %d\n", nbBombs);
            for (auto p : players) {
                p->setPos(getPos(p->getID(), playersPositions));
            }
//            for (int i = 0; i < nbBombs; i += 2) {
//                world.addEntity(new gzzzt::ClientBomb(sf::Vector2f(bombsPositions[i], bombsPositions[i + 1])));
//            }
            delete resp;
        }

        // update
        sf::Time elapsed = clock.restart();
        world.update(elapsed.asSeconds());

        // render
        window.clear(sf::Color::White);
        world.render(window);
        window.display();
    }
    stopThreads();
    receiver.join();
    tcpManager.disconnect();
    return 0;
}

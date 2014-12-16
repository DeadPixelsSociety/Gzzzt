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
#include <thread>

#include <gzzzt/server/Game.h>
#include <gzzzt/server/ServerPlayer.h>
#include <gzzzt/server/ServerPlayerList.h>
#include <gzzzt/server/ServerTCPManager.h>
#include <gzzzt/server/ServerUDPManager.h>
#include <gzzzt/server/Physics.h>
#include <gzzzt/server/ServerMap.h>

#include <gzzzt/shared/ConcurrentQueue.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/GameStateResponse.h>
#include <gzzzt/shared/IdentifyRequest.h>
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/NewPlayerResponse.h>
#include <gzzzt/shared/StartGameResponse.h>

#include "config.h"
#include "gzzzt/server/Physics.h"
#include "gzzzt/server/ServerMap.h"
#include "gzzzt/shared/Resource.h"

#define DEFAULT_TCP_PORT 5000
#define DEFAULT_UDP_PORT 5001

static std::atomic_bool should_continue
{
    true
};

static void help(void) {
    std::cout << "Usage: gzzzt-server [TCP_PORT] [UDP_PORT]" << std::endl;
}

static void signal_handler(int sig) {
    assert(sig == SIGINT || sig == SIGTERM);
    should_continue = false;
}

static void receiveMsg(gzzzt::ServerUDPManager& udpManager, gzzzt::ConcurrentQueue<gzzzt::Request*>& inQueue) {
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Starting the receiving thread...\n");
    gzzzt::Request* req;
    while (should_continue) {
        req = udpManager.receive();
        if (req != nullptr) {
            inQueue.push(req);
        }
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Stopping the receiving thread...\n");
}

static void broadcastMsg(gzzzt::ServerUDPManager& udpManager,
        gzzzt::ConcurrentQueue<gzzzt::Response*>& outQueue,
        const gzzzt::ServerPlayerList& players) {
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Starting the broadcasting thread...\n");
    gzzzt::Response* resp;
    while (should_continue) {
        if (!outQueue.empty()) {
            resp = outQueue.pop();
            if (resp != nullptr) {
                gzzzt::Log::debug(gzzzt::Log::NETWORK, "Broadcast response\n");
                if (!udpManager.broadcast(players, *resp)) {
                    gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not broadcast msg\n");
                }
                delete resp;
            }
        }
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Stopping the broadcasting thread...\n");
}

static std::vector<float> getPlayersPosition(const gzzzt::ServerPlayerList& players) {
    std::vector<float> positions;
    positions.push_back(static_cast<float> (players.getSize()));
    for (auto& p : players) {
        positions.push_back(static_cast<float> (p->getID()));
        positions.push_back(p->getBody()->pos.x);
        positions.push_back(p->getBody()->pos.y);
    }
    return positions;
}

int main(int argc, char** argv) {
    if (argc > 3) {
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

    unsigned short port = argc <= 1 ? DEFAULT_TCP_PORT : std::strtoul(argv[1], nullptr, 10);
    unsigned short udpPort = argc <= 2 ? DEFAULT_UDP_PORT : std::strtoul(argv[2], nullptr, 10);

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

    // Initialize the UDP socket
    gzzzt::ServerUDPManager udpManager(udpPort);
    if (!udpManager.init()) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not bind UDP socket\n");
        tcpManager.close();
        return 5;
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "UDP socket created\n");

    // Broadcast the players list
    std::map<uint8_t, std::string> playersData;
    for (auto player : players) {
        gzzzt::Log::error(gzzzt::Log::NETWORK, "-> %s(%d)\n", player->getName().c_str(), player->getID());
        playersData.insert(std::pair<uint8_t, std::string>(player->getID(), player->getName()));
    }
    if (!tcpManager.broadcast(players, gzzzt::StartGameResponse(playersData, udpPort))) {
        gzzzt::Log::fatal(gzzzt::Log::NETWORK, "Error while broadcasting to the players\n");
    }

    // Get the players UDP port
    uint8_t nbPlayersReq = 0;
    while (should_continue && nbPlayersReq < players.getSize()) {
        if (!udpManager.receiveIdentifyRequest(players)) {
            gzzzt::Log::error(gzzzt::Log::NETWORK, "Could not associate players to UDP port\n");
            udpManager.close();
            tcpManager.close();
            return 6;
        }
        nbPlayersReq++;
    }
    gzzzt::Log::info(gzzzt::Log::NETWORK, "Players :\n");
    for (auto& p : players) {
        gzzzt::Log::info(gzzzt::Log::NETWORK, "Player #%d = %s (%s:%d, UDP = %d)\n",
                p->getID(), p->getName().c_str(), p->getAddress().toString().c_str(),
                p->getTCPPort(), p->getUDPPort());
    }

    // Create concurrent queues for the messages
    gzzzt::ConcurrentQueue<gzzzt::Request*> inQueue;
    gzzzt::ConcurrentQueue<gzzzt::Response*> outQueue;

    // Launch the threads
    std::thread receiver(&receiveMsg, std::ref(udpManager), std::ref(inQueue));
    std::thread broadcaster(&broadcastMsg, std::ref(udpManager), std::ref(outQueue), std::ref(players));

    // initialize
    gzzzt::Game game;
    gzzzt::Physics physics;
    gzzzt::ResourceManager resourceManager;

    resourceManager.addSearchDir(GAME_DATADIR);
    resourceManager.addSearchDir("..");

    // load resources
    gzzzt::ServerMap serverMap("maps/simple/simple.tmx", resourceManager);
    serverMap.load(&physics);
    int playerLayer = 0;
    for (auto& p : players) {
        physics.addBody(p->getBody());
        p->getBody()->layers = playerLayer;
        playerLayer++;
    }

    // send the players position
    std::vector<float> playersPositions = getPlayersPosition(players);
    gzzzt::GameStateResponse* resp = new gzzzt::GameStateResponse(playersPositions);
    outQueue.push(resp);

    // main loop
    sf::Clock clock;

    while (should_continue) {
        if (!inQueue.empty()) {
            gzzzt::Request* req = inQueue.pop();
            gzzzt::ServerPlayer* player = players.getById(req->getPlayerId());
            if (req->getReqType() == gzzzt::RequestType::ACTION) {
                gzzzt::ActionRequest* actionReq = dynamic_cast<gzzzt::ActionRequest*> (req);
                gzzzt::Body* playerBody = player->getBody();
                std::bitset<4> keys = actionReq->getKeys();
                playerBody->velocity.x = 0.f;
                playerBody->velocity.y = 0.f;
                if (keys.test(MOVE_UP)) {
                    playerBody->velocity.y = -64.f;
                }
                if (keys.test(MOVE_DOWN)) {
                    playerBody->velocity.y = 64.f;
                }
                if (keys.test(MOVE_LEFT)) {
                    playerBody->velocity.x = -64.f;
                }
                if (keys.test(MOVE_RIGHT)) {
                    playerBody->velocity.x = 64.f;
                }
            }
            delete req;

        }

        // update
        sf::Time elapsed = clock.restart();
        physics.update(elapsed.asSeconds());
        game.update(elapsed.asSeconds());

        sf::sleep(sf::milliseconds(16));

        // broadcast response
        std::vector<float> playersPositions = getPlayersPosition(players);
        gzzzt::GameStateResponse* resp = new gzzzt::GameStateResponse(playersPositions);
        outQueue.push(resp);
    }

    gzzzt::Log::info(gzzzt::Log::GENERAL, "Stopping the server...\n");

    // Stop the threads
    receiver.join();
    broadcaster.join();
    // Close the connections
    tcpManager.close();
    udpManager.close();
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Server stopped!\n");
    return 0;
}

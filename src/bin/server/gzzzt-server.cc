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
#include <atomic>
#include <iostream>

#include <SFML/System.hpp>

#include <gzzzt/server/Game.h>
#include <gzzzt/shared/Log.h>

#include "config.h"

static std::atomic_bool should_continue {true};

static void signal_handler(int sig) {
    assert(sig == SIGINT || sig == SIGTERM);
    should_continue = false;
}

int main(void) {
    std::cout << "Gzzzt-Server (version " << GAME_VERSION << ")" << std::endl;

    gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
    gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the server...\n");
    gzzzt::Log::info(gzzzt::Log::GENERAL, "You can stop it with CTRL+C or with the kill command.\n");

    auto previous_sigint_handler = std::signal(SIGINT, signal_handler);

    if (previous_sigint_handler == SIG_ERR) {
        gzzzt::Log::error(gzzzt::Log::GENERAL, "Could not set the signal handler for SIGINT\n");
        return 1;
    }

    auto previous_sigterm_handler = std::signal(SIGTERM, signal_handler);

    if (previous_sigterm_handler == SIG_ERR) {
        gzzzt::Log::error(gzzzt::Log::GENERAL, "Could not set the signal handler for SIGTERM\n");
        return 1;
    }


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

    return 0;
}

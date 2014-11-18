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

#include <SFML/Graphics.hpp>

#include <gzzzt/client/SoundHandler.h>
#include <gzzzt/shared/Log.h>

#include "config.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Sounds prototype", sf::Style::Default, settings);
    window.setKeyRepeatEnabled(false);

    gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
    gzzzt::ResourceManager manager;

    manager.addSearchDir(GAME_DATADIR);

    gzzzt::SoundHandler handler(manager);

    // main loop

    while (window.isOpen()) {
        // input
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {
                    case sf::Keyboard::A:
                        gzzzt::Log::info(gzzzt::Log::GENERAL, "Game In!\n");
                        handler.play(gzzzt::Sound::GAME_IN);
                        break;

                    case sf::Keyboard::Z:
                        handler.play(gzzzt::Sound::GAME_START);
                        break;

                    case sf::Keyboard::E:
                        handler.play(gzzzt::Sound::GAME_END);
                        break;

                    case sf::Keyboard::R:
                        handler.play(gzzzt::Sound::BOMB_DROP);
                        break;

                    case sf::Keyboard::T:
                        handler.play(gzzzt::Sound::BOMB_EXPLODE);
                        break;

                    case sf::Keyboard::Y:
                        handler.play(gzzzt::Sound::DEATH);
                        break;

                    default:
                        break;
                }

            }
        }

        // render
        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}

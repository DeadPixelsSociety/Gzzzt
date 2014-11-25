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
#include <gzzzt/client/World.h>
#include <gzzzt/client/ClientMap.h>
#include <gzzzt/client/Resource.h>

#include "config.h"

int main(void) {
    // initialize
    gzzzt::World world;
    gzzzt::ClientMap* map;
    gzzzt::ResourceManager resourceManager;
    
    resourceManager.addSearchDir(GAME_DATADIR);
    
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Gzzzt (version " GAME_VERSION ")");
    window.setKeyRepeatEnabled(false);

    // load resources
    
#if _DEBUG_
    resourceManager.addSearchDir("..");
    map = new gzzzt::ClientMap("../../../src/share/gzzzt/maps/simple/simple.tmx", resourceManager);
#else
    assert(true);
#endif
    
    // add entities
    world.addEntity(map);

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

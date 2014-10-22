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

#include <cstdio>
#include <vector>

#include <SFML/Graphics.hpp>

#include <gzzzt/server/Physics.h>
#include <gzzzt/shared/Log.h>

class Entity {
public:
    virtual ~Entity() {

    }

    virtual void update(float dt) {
        // default: do nothing
    }

    virtual void render(sf::RenderWindow& window) {
        // default: do nothing
    }

    gzzzt::Body body;
};

#define RADIUS 20

class Ball : public Entity {
public:
    Ball(float x, float y, float dx, float dy) {
        body.type = gzzzt::Body::DYNAMIC;
        body.pos.x = x;
        body.pos.y = y;
        body.velocity.x = dx;
        body.velocity.y = dy;
        body.shape.kind = gzzzt::Shape::CIRCLE;
        body.shape.circle.radius = RADIUS;
        body.restitution = 0.0f;
    }

    virtual void render(sf::RenderWindow& window) override {
        sf::CircleShape shape(RADIUS);
        shape.setOrigin(RADIUS, RADIUS);
        shape.setPosition(body.pos);
        shape.setFillColor(sf::Color::Red);

        window.draw(shape);
    }
};

class Block : public Entity {
public:
    Block(float x, float y, float dx, float dy) {
        body.type = gzzzt::Body::STATIC;
        body.pos.x = x;
        body.pos.y = y;
        body.velocity.x = dx;
        body.velocity.y = dy;
        body.shape.kind = gzzzt::Shape::RECTANGLE;
        body.shape.rectangle.width = body.shape.rectangle.height = 2 * RADIUS;
        body.restitution = 0.0f;
    }

    virtual void render(sf::RenderWindow& window) override {
        sf::RectangleShape shape({ body.shape.rectangle.width, body.shape.rectangle.height });
        shape.setOrigin(body.shape.rectangle.width / 2.0f, body.shape.rectangle.height / 2.0f);
        shape.setPosition(body.pos);
        shape.setFillColor(sf::Color::Green);

        window.draw(shape);
    }
};


class World {
public:

    Ball *addBall(float x, float y, float dx, float dy) {
        auto e = new Ball(x, y, dx, dy);
        engine.addBody(&e->body);
        entities.push_back(e);
        return e;
    }

    void addBlock(float x, float y, float dx, float dy) {
        auto e = new Block(x, y, dx, dy);
        engine.addBody(&e->body);
        entities.push_back(e);
    }

    void clear() {
        engine.clear();

        for (auto entity : entities) {
            delete entity;
        }

        entities.clear();
    }

    void update(float dt) {
        engine.update(dt);

        for (auto entity : entities) {
            entity->update(dt);
        }
    }

    void render(sf::RenderWindow& window) {
        for (auto entity : entities) {
            entity->render(window);
        }
    }


private:
    gzzzt::Physics engine;
    std::vector<Entity *> entities;
};


static void setupDemo(World& world, int step) {
    world.clear();

    switch (step) {
        case 1:
            std::printf("Step %i: One ball and one block with no restitution\n", step);
            world.addBlock(400, 250, 0, 0);
            world.addBall(100, 250, 200, 0);
            break;

        case 2:
            std::printf("Step %i: One ball and one block with some restitution\n", step);
            world.addBlock(400, 250, 0, 0);
            world.addBall(100, 250, 200, 0)->body.restitution = 0.5f;
            break;

        case 3:
            std::printf("Step %i: Multiple balls colliding\n", step);

            for (int i = 0; i < 4; ++i) {
                world.addBall(250 - 3 * RADIUS + i * RADIUS * 2, 250, 0, 0)->body.restitution = 1.0f;
            }

            world.addBall(50, 250, 200, 0)->body.restitution = 1.0f;

        default:
            break;
    }
}


int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Physics prototype", sf::Style::Default, settings);
    window.setKeyRepeatEnabled(false);

    sf::View view({ 0.0f, 0.0f, 500.0f, 500.0f });
    window.setView(view);

    //   gzzzt::Log::setLevel(gzzzt::Log::PHYSICS, gzzzt::Log::DEBUG);

    World world;

    int step = 0;
    std::printf("Press SPACE to start the demo!\n");

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

                    case sf::Keyboard::Space:
                        step++;
                        setupDemo(world, step);
                        break;

                    case sf::Keyboard::BackSpace:
                        step--;
                        setupDemo(world, step);
                        break;

                    case sf::Keyboard::Return:
                        setupDemo(world, step);
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

    world.clear();

    return 0;
}

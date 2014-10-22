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
#ifndef GZZZT_SERVER_BODY_H
#define GZZZT_SERVER_BODY_H

#include <SFML/System/Vector2.hpp>

namespace gzzzt {

    struct Shape {
        enum Kind : unsigned {
            CIRCLE = 0,
            RECTANGLE = 1,
        };

        Kind kind;
        union {
            struct {
                float radius;
            } circle;

            struct {
                float width;
                float height;
            } rectangle;
        };
    };

    struct Body;

    struct Manifold {
        Body *a;
        Body *b;
        float penetration;
        sf::Vector2f normal;
    };

    struct Body {
        enum Type {
            STATIC,
            DYNAMIC,
        };

        Type type;
        sf::Vector2f pos; /**< center of the body */
        sf::Vector2f velocity;
        Shape shape;

        static bool collides(const Body& lhs, const Body& rhs, Manifold *m);
    };

}

#endif // GZZZT_SERVER_BODY_H

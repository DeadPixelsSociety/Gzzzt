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
#include <gzzzt/server/Physics.h>

namespace gzzzt {

    void Physics::addBody(Body *body) {
        switch (body->type) {
            case Body::DYNAMIC:
                m_dynamic_bodies.push_back(body);
                break;

            case Body::STATIC:
                m_static_bodies.push_back(body);
                break;
        }
    }

    void Physics::update(float dt) {
        // speed simulation
        for (auto& body : m_dynamic_bodies) {
            body->pos.x += body->speed.dx * dt;
            body->pos.y += body->speed.dy * dt;
        }

        // collision resolution
        Manifold m;
        std::vector<Manifold> manifolds;

        for (auto& body : m_dynamic_bodies) {
            for (auto& other_body : m_dynamic_bodies) {
                if (body == other_body) {
                    continue;
                }

                if (body < other_body) {
                    // avoid adding the manifold twice
                    continue;
                }

                if (Body::collides(*body, *other_body, &m)) {
                    manifolds.push_back(m);
                }
            }

            for (auto& other_body : m_static_bodies) {
                if (Body::collides(*body, *other_body, &m)) {
                    manifolds.push_back(m);
                }
            }
        }

        for (auto m : manifolds) {
            // TODO
        }

    }

}

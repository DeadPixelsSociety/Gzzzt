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

#include <cassert>

namespace gzzzt {
    static float dotProduct(const sf::Vector2f& rhs, const sf::Vector2f& lhs) {
        return rhs.x * lhs.x + rhs.y * lhs.y;
    }

    static void resolveCollision(Manifold& m) {
        assert(m.a && m.b);

        sf::Vector2f relative_velocity = m.b->velocity - m.a->velocity;
        float velocity_along_normal = dotProduct(relative_velocity, m.normal);

        if (velocity_along_normal > 0) {
            return;
        }

        float a_inverse_mass = (m.a->type == Body::DYNAMIC ? 1.0f : 0.0f);
        float b_inverse_mass = (m.b->type == Body::DYNAMIC ? 1.0f : 0.0f);

        float restitution = std::max(m.a->restitution, m.b->restitution);

        float j = -(1 + restitution) * velocity_along_normal / (a_inverse_mass + b_inverse_mass);

        sf::Vector2f impulse = j * m.normal;
        m.a->velocity -= a_inverse_mass * impulse;
        m.b->velocity -= b_inverse_mass * impulse;
    }

    static void correctPosition(Manifold& m) {
        const float percent = 0.2;
        const float slop = 0.01;

        float a_inverse_mass = (m.a->type == Body::DYNAMIC ? 1.0f : 0.0f);
        float b_inverse_mass = (m.b->type == Body::DYNAMIC ? 1.0f : 0.0f);

        sf::Vector2f correction = std::max(m.penetration - slop, 0.0f) / (a_inverse_mass + b_inverse_mass) * percent * m.normal;

        m.a->pos -= a_inverse_mass * correction;
        m.b->pos += b_inverse_mass * correction;
    }

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
            body->pos.x += body->velocity.x * dt;
            body->pos.y += body->velocity.y * dt;
        }

        // collision resolution
        Manifold m;
        std::vector<Manifold> manifolds;

        for (auto body : m_dynamic_bodies) {
            m.a = body;

            for (auto other_body : m_dynamic_bodies) {
                if (body == other_body) {
                    continue;
                }

                if (body < other_body) {
                    // avoid adding the manifold twice
                    continue;
                }

                if (Body::collides(*body, *other_body, &m)) {
                    m.b = other_body;
                    manifolds.push_back(m);
                }
            }

            for (auto other_body : m_static_bodies) {
                if (Body::collides(*body, *other_body, &m)) {
                    m.b = other_body;
                    manifolds.push_back(m);
                }
            }
        }

        for (auto& m : manifolds) {
            resolveCollision(m);
        }

        for (auto& m : manifolds) {
            correctPosition(m);
        }
    }

}

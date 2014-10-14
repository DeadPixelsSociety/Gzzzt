/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GZZZT_WORLD_H
#define GZZZT_WORLD_H

#include <functional>
#include <map>
#include <type_traits>
#include <vector>

#include <SFML/Graphics.hpp>

#include <gzzzt/client/ClientEntity.h>
#include <gzzzt/client/Event.h>

namespace gzzzt {
    enum class Memory {
        FROM_HEAP,
        FROM_STACK,
    };

    class World {
    public:

        void update(float dt);
        void render(sf::RenderWindow& window);

        void addEntity(ClientEntity *e, Memory from = Memory::FROM_HEAP);
        void removeEntity(ClientEntity *e);

        void registerHandler(EventType type, EventHandler handler);

        template<typename E>
        void registerHandler(EventHandler handler) {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_EVENT, "E must define its type");
            registerHandler(E::type, handler);
        }

        template<typename E, typename R, typename T>
        void registerHandler(R T::*pm, T *obj) {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_EVENT, "E must define its type");
            registerHandler(E::type, std::bind(pm, obj));
        }

        void triggerEvent(ClientEntity *origin, EventType type, Event *event);

        template<typename E>
        void triggerEvent(ClientEntity *origin, E *event) {
            static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
            static_assert(E::type != INVALID_EVENT, "E must define its type");
            triggerEvent(origin, E::type, event);
        }

    private:

        class ClientEntityPtr {
        public:
            ClientEntityPtr(ClientEntity *entity, std::function<void(ClientEntity *)> deleter)
                : m_entity(entity)
                , m_deleter(deleter) {
            }

            ClientEntityPtr(const ClientEntityPtr&) = delete;
            ClientEntityPtr& operator=(const ClientEntityPtr&) = delete;

            ClientEntityPtr(ClientEntityPtr&& other)
                : m_entity(other.m_entity)
                , m_deleter(std::move(other.m_deleter)) {
            }

            ClientEntityPtr& operator=(ClientEntityPtr && other) {
                m_deleter(m_entity);
                m_entity = other.m_entity;
                m_deleter = std::move(other.m_deleter);
                return *this;
            }

            ~ClientEntityPtr() {
                m_deleter(m_entity);
            }

            ClientEntity *get() {
                return m_entity;
            }

            const ClientEntity *get() const {
                return m_entity;
            }

            ClientEntity *operator->() {
                return get();
            }

            const ClientEntity *operator->() const {
                return get();
            }

            ClientEntity& operator*() {
                return *get();
            }

            const ClientEntity& operator*() const {
                return *get();
            }

        private:
            ClientEntity *m_entity;
            std::function<void(ClientEntity *)> m_deleter;
        };

        std::vector<ClientEntityPtr> m_entities;
        std::map<EventType, std::vector<EventHandler>> m_handlers;
    };


}


#endif // GZZZT_WORLD_H

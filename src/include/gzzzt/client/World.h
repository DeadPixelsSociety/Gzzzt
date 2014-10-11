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
#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <functional>
#include <map>
#include <type_traits>
#include <vector>

#include <SFML/Graphics.hpp>

#include <gzzzt/client/Entity.h>
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

    void addEntity(Entity *e, Memory from = Memory::FROM_HEAP);
    void removeEntity(Entity *e);

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

    void triggerEvent(Entity *origin, EventType type, Event *event);

    template<typename E>
    void triggerEvent(Entity *origin, E *event) {
      static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
      static_assert(E::type != INVALID_EVENT, "E must define its type");
      triggerEvent(origin, E::type, event);
    }

  private:

    class EntityPtr {
    public:
      EntityPtr(Entity *entity, std::function<void(Entity*)> deleter)
      : m_entity(entity)
      , m_deleter(deleter)
      {
      }

      EntityPtr(const EntityPtr&) = delete;
      EntityPtr& operator=(const EntityPtr&) = delete;

      EntityPtr(EntityPtr&& other)
      : m_entity(other.m_entity)
      , m_deleter(std::move(other.m_deleter)) {
      }

      EntityPtr& operator=(EntityPtr&& other) {
        m_deleter(m_entity);
        m_entity = other.m_entity;
        m_deleter = std::move(other.m_deleter);
        return *this;
      }

      ~EntityPtr() {
        m_deleter(m_entity);
      }

      Entity *get() {
        return m_entity;
      }

      const Entity *get() const {
        return m_entity;
      }

      Entity *operator->() {
        return get();
      }

      const Entity *operator->() const {
        return get();
      }

      Entity& operator*() {
        return *get();
      }

      const Entity& operator*() const {
        return *get();
      }

    private:
      Entity *m_entity;
      std::function<void(Entity*)> m_deleter;
    };

    std::vector<EntityPtr> m_entities;
    std::map<EventType, std::vector<EventHandler>> m_handlers;
  };


}


#endif // GAME_WORLD_H

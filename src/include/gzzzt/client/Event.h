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
#ifndef GZZZT_EVENT_H
#define GZZZT_EVENT_H

#include <cstdint>
#include <functional>


namespace gzzzt {
  class Entity;

  typedef uint64_t EventType;

#define INVALID_EVENT 0

  constexpr EventType Hash(const char *str, std::size_t sz) {
    return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
  }

  inline EventType Hash(const std::string& str) {
    return Hash(str.c_str(), str.size());
  }


  struct Event {
    static const EventType type = INVALID_EVENT;
  };

  enum class EventStatus {
    KEEP, /**< The handler must be kept */
    DIE,  /**< The handler can be removed */
  };

  typedef std::function<EventStatus(Entity*, EventType, Event*)> EventHandler;

}

constexpr gzzzt::EventType operator"" _type(const char *str, std::size_t sz) {
  return gzzzt::Hash(str, sz);
}

#endif // GZZZT_EVENT_H

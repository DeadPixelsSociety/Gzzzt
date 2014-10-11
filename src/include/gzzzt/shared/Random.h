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
#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include <random>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace gzzzt {

  class Random {
  public:
    Random();
    Random(unsigned seed);

    int computeUniformInteger(int min, int max);

    float computeUniformFloat(float min, float max);

    float computeNormalFloat(float mean, float stddev);

  private:
    std::mt19937 m_engine;
  };

}

#endif // GAME_RANDOM_H

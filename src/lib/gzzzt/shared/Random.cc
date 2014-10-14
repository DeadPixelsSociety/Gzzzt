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
#include <gzzzt/shared/Random.h>

#include <ctime>

namespace gzzzt {

    Random::Random()
        : m_engine(std::time(nullptr)) {

    }

    Random::Random(unsigned seed)
        : m_engine(seed) {

    }


    int Random::computeUniformInteger(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(m_engine);
    }

    float Random::computeUniformFloat(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(m_engine);
    }

    float Random::computeNormalFloat(float mean, float stddev) {
        std::normal_distribution<float> dist(mean, stddev);
        return dist(m_engine);
    }

}

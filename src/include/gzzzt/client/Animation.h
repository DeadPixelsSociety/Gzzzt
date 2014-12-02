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
#ifndef GZZZT_ANIMATION_H
#define GZZZT_ANIMATION_H

#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <gzzzt/client/ClientEntity.h>

namespace gzzzt {

    struct AnimationFrame {
        sf::Texture *texture;
        sf::IntRect bounds;
        float duration;
    };

    class Animation {
    public:

        Animation(std::string name)
        : m_name(std::move(name)) {
        }

        const std::string& name() {
            return m_name;
        }

        void addFrame(const AnimationFrame& frame);

        void update(float dt);

        sf::Texture *currentTexture();
        sf::IntRect currentTextureRect();

    private:
        std::string m_name;
        std::size_t m_current_frame = 0;
        float m_current_duration_in_frame = 0.0f;
        std::vector<AnimationFrame> m_frames;
    };

}

#endif // GZZZT_ANIMATION_H

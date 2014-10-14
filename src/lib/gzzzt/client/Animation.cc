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
#include <gzzzt/client/Animation.h>

#include <iostream>

namespace gzzzt {

    void Animation::addFrame(const AnimationFrame& frame) {
        if (m_frames.empty()) {
            m_current_duration_in_frame = frame.duration;
            m_current_frame = 0;
        }

        m_frames.push_back(frame);
    }

    void Animation::update(float dt) {
        if (m_frames.empty()) {
            return;
        }

        m_current_duration_in_frame -= dt;

        while (m_current_duration_in_frame < 0) {
            m_current_frame = (m_current_frame + 1) % m_frames.size();
            m_current_duration_in_frame += m_frames[m_current_frame].duration;
        }
    }

    sf::Texture *Animation::currentTexture() {
        if (m_frames.empty()) {
            std::cerr << "Error! The animation does not have any frame: " << name() << std::endl;
            return nullptr;
        }

        return m_frames[m_current_frame].texture;
    }

    sf::IntRect Animation::currentTextureRect() {
        if (m_frames.empty()) {
            std::cerr << "Error! The animation does not have any frame: " << name() << std::endl;
            return sf::IntRect();
        }

        return m_frames[m_current_frame].bounds;
    }

}

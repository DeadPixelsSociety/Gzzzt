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
#include <gzzzt/client/SoundHandler.h>

namespace gzzzt {

    SoundHandler::SoundHandler(ResourceManager& manager) {
        // Loading all sounds needed by the game
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/EnteringGame.ogg"));
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/StartGame.ogg"));
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/EndGame.ogg"));
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/BombDrop.ogg"));
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/BombExplode.ogg"));
        m_SoundsBuffer.push_back(manager.getSoundBuffer("sound/Death.ogg"));
    }

    void SoundHandler::play(Sound id){
        sf::Sound sound;

        switch (id){
            case Sound::GAME_IN:
                sound.setBuffer(*m_SoundsBuffer.at(0));
                break;
            case Sound::GAME_START:
                sound.setBuffer(*m_SoundsBuffer.at(1));
                break;
            case Sound::GAME_END:
                sound.setBuffer(*m_SoundsBuffer.at(2));
                break;
            case Sound::BOMB_DROP:
                sound.setBuffer(*m_SoundsBuffer.at(3));
                break;
            case Sound::BOMB_EXPLODE:
                sound.setBuffer(*m_SoundsBuffer.at(4));
                break;
            case Sound::DEATH:
                sound.setBuffer(*m_SoundsBuffer.at(5));
                break;
        }

        sound.play();
    }

} /* namespace gzzzt */

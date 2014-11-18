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

#include <gzzzt/shared/Log.h>

namespace gzzzt {

    SoundHandler::SoundHandler(ResourceManager& manager) {
        // Loading all sounds needed by the game
        load(manager, "sounds/EnteringGame.ogg");
        load(manager, "sounds/StartGame.ogg");
        load(manager, "sounds/EndGame.ogg");
        load(manager, "sounds/BombDrop.ogg");
        load(manager, "sounds/BombExplode.ogg");
        load(manager, "sounds/Death.ogg");
    }

    void SoundHandler::play(Sound id){
        switch (id) {
            case Sound::GAME_IN:
                Log::info(Log::GENERAL, "Inside play!\n");
                m_SoundPlayer.at(0).play();
                break;
            case Sound::GAME_START:
                m_SoundPlayer.at(1).play();
                break;
            case Sound::GAME_END:
                m_SoundPlayer.at(2).play();
                break;
            case Sound::BOMB_DROP:
                m_SoundPlayer.at(3).play();
                break;
            case Sound::BOMB_EXPLODE:
                m_SoundPlayer.at(4).play();
                break;
            case Sound::DEATH:
                m_SoundPlayer.at(5).play();
                break;
        }
    }
    
    void SoundHandler::load(ResourceManager& manager, const std::string& filename){
        auto soundBuffer = manager.getSoundBuffer(filename);
        m_SoundsBuffer.push_back(soundBuffer);
        sf::Sound sound;
        sound.setBuffer(*soundBuffer);
        m_SoundPlayer.push_back(sound);
    }

} /* namespace gzzzt */

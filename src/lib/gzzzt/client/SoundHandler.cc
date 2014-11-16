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

    SoundHandler::SoundHandler() {
        //Loading all sounds needed by the game
        sf::SoundBuffer buffer;
        if(buffer.loadFromFile("../src/res/gzzzt/sound/EnteringGame.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/StartGame.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/EndGame.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/BombDrop.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/BombExplode.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/Death.ogg"))
            m_SoundsBuffer.push_back(buffer);
    }

    SoundHandler::~SoundHandler() {
        m_SoundsBuffer.clear();
    }
    
    void SoundHandler::play(int s){
        switch(s){
            case ENTERGAME:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(0));
                break;
            case STARTGAME:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(1));
                break;
            case ENDGAME:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(2));
                break;
            case BOMBDROP:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(3));
                break;
            case BOMBEXPLODE:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(4));
                break;
            case DEATH:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(5));
                break;

            default:
                break;
        }
        m_SoundPlayer.play();
    }

} /* namespace gzzzt */

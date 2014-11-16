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
        if(buffer.loadFromFile("../src/res/gzzzt/sound/EnteringGame.mp3"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/Countdown-A.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/Countdown-B.ogg"))
            m_SoundsBuffer.push_back(buffer);
        if(buffer.loadFromFile("../src/res/gzzzt/sound/EndGame.ogg"))
            m_SoundsBuffer.push_back(buffer);
    }

    SoundHandler::~SoundHandler() {
    }
    
    void SoundHandler::play(int s){
        switch(s){
            case ENTERGAME:
                m_SoundPlayer.setBuffer(m_SoundsBuffer.at(0));
                break;
            case STARTGAME:
                break;
            case ENDGAME:
                break;
            case BOMBDROP:
                break;
            case BOMBEXPLODE:
                break;
            case DEATH:
                break;

            default:
                break;
        }
        m_SoundPlayer.play();
    }

} /* namespace gzzzt */

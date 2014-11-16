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
#ifndef GZZZT_SOUNDHANDLER_H
#define GZZZT_SOUNDHANDLER_H

#include <vector>

#include <SFML/Audio.hpp>

namespace gzzzt {

    class SoundHandler {
    public:
        SoundHandler();
        virtual ~SoundHandler();
        void play(int s);
        
        // Const var for sound played
        static const int ENTERGAME = 0;
        static const int STARTGAME = 1;
        static const int ENDGAME = 2;
        static const int BOMBDROP = 3;
        static const int BOMBEXPLODE = 4;
        static const int DEATH = 5;
    private:
        std::vector<sf::SoundBuffer> m_SoundsBuffer;
        sf::Sound m_SoundPlayer;
    };

}

#endif // GZZZT_SOUNDHANDLER_H

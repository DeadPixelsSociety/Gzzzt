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
#ifndef GZZZT_SERVER_TCP_MANAGER_H
#define GZZZT_SERVER_TCP_MANAGER_H

#include <SFML/Network.hpp>

#include <gzzzt/server/ServerPlayerList.h>
#include <gzzzt/shared/Response.h>

namespace gzzzt {

    class ServerTCPManager {
    public:
        explicit ServerTCPManager(unsigned short port);

        bool init();
        void close();
        bool waitPlayers(int nbPlayers, gzzzt::ServerPlayerList& players);
        bool broadcast(gzzzt::ServerPlayerList& players, const gzzzt::Response& msg) const;

    private:
        unsigned short m_port;
        sf::TcpListener m_listener;
        sf::SocketSelector m_selector;

        bool isDuplicatedName(const gzzzt::ServerPlayerList& players, const std::string& name) const;
    };

}

#endif // GZZZT_SERVER_TCP_MANAGER_H

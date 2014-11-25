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
#ifndef GZZZT_SERVER_UDP_MANAGER_H
#define GZZZT_SERVER_UDP_MANAGER_H

#include <SFML/Network.hpp>

#include <gzzzt/server/ServerPlayerList.h>
#include <gzzzt/shared/ActionRequest.h>
#include <gzzzt/shared/Response.h>

namespace gzzzt {

    class ServerUDPManager {
    public:
        explicit ServerUDPManager(unsigned short port);
        virtual ~ServerUDPManager();

        bool init();
        void close();

        bool broadcast(const gzzzt::ServerPlayerList& players, const gzzzt::Response& resp);
        bool send(const gzzzt::ServerPlayer& player, const gzzzt::Response& resp);
        gzzzt::Request* receive();
        bool receiveIdentifyRequest(gzzzt::ServerPlayerList& players);

    private:
        sf::UdpSocket m_socket;
        unsigned short m_port;
    };

}

#endif // GZZZT_SERVER_UDP_MANAGER_H

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
#ifndef GZZZT_CLIENT_TCP_MANAGER_H
#define GZZZT_CLIENT_TCP_MANAGER_H

#include <list>
#include <string>

#include <SFML/Network.hpp>

#include <gzzzt/client/ClientPlayer.h>
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/GameStateResponse.h>
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/NewPlayerResponse.h>
#include <gzzzt/shared/Request.h>
#include <gzzzt/shared/Response.h>
#include <gzzzt/shared/StartGameResponse.h>

namespace gzzzt {

    class ClientTCPManager {
    public:
        explicit ClientTCPManager(std::string serverAddress, unsigned short serverPort);

        std::string getServerAddress() const;
        unsigned short getServerPort() const;

        bool connect();
        void disconnect();
        virtual bool send(const gzzzt::Request& req);
        Response* receive();

        bool declareAsNewPlayer(const std::string& name, std::string& error);
        bool receiveGameData(std::list<gzzzt::ClientPlayer>& players, unsigned short& serverPortUDP, std::string& error);

    private:
        sf::TcpSocket m_socket;
        std::string m_serverAddress;
        unsigned short m_serverPort;
    };

}

#endif // GZZZT_CLIENT_TCP_MANAGER_H

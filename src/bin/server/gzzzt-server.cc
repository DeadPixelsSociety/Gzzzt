/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

#include <gzzzt/shared/Log.h>

#include "config.h"

int main(void) {
	std::cout << "Gzzzt-Server (version " << GAME_VERSION << ")" << std::endl;

  gzzzt::Log::setLevel(gzzzt::Log::DEBUG);
  gzzzt::Log::info(gzzzt::Log::GENERAL, "Starting the server...\n");


	return 0;
}

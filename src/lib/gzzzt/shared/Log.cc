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
#include <gzzzt/shared/Log.h>

#include <cassert>
#include <ctime>

namespace gzzzt {

    // default values
    std::map<Log::Category, Log::Level> Log::s_levels = {
        { Log::GENERAL, Log::WARN },
        { Log::RENDER,  Log::WARN },
        { Log::NETWORK, Log::WARN },
        { Log::PHYSICS, Log::WARN },
    };

    void Log::setLevel(Level level) {
        for (auto& item : s_levels) {
            item.second = level;
        }
    }

    void Log::setLevel(Category category, Level level) {
        s_levels[category] = level;
    }

    static const char *levelToString(Log::Level level) {
        switch (level) {
            case Log::DEBUG:
                return "DEBUG";

            case Log::INFO:
                return "INFO";

            case Log::WARN:
                return "WARN";

            case Log::ERROR:
                return "ERROR";

            case Log::FATAL:
                return "FATAL";
        }

        assert(false);
        return "?";
    }

    static const char *categoryToString(Log::Category category) {
        switch (category) {
            case Log::GENERAL:
                return "GENERAL";

            case Log::RENDER:
                return "RENDER";

            case Log::NETWORK:
                return "NETWORK";

            case Log::PHYSICS:
                return "PHYSICS";
        }

        assert(false);
        return "?";
    }

    void Log::log(Level level, Category category, const char *fmt, va_list ap) {
        if (level < s_levels[category]) {
            return;
        }

        unsigned long t = std::time(nullptr);
        std::fprintf(stderr, "[%lu][%s][%s] ", t, levelToString(level), categoryToString(category));

        std::vfprintf(stderr, fmt, ap);
    }

}

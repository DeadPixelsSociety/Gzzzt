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
#ifndef GZZZT_LOG_H
#define GZZZT_LOG_H

#include <cstdarg>
#include <cstdlib>
#include <map>

namespace gzzzt {

    class Log {
    public:
        enum Level : int {
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
        };

        enum Category : int {
            GENERAL,
            RENDER,
            NETWORK,
            PHYSICS,
        };

        static void setLevel(Level level);

        static void setLevel(Category category, Level level);

        static void debug(Category category, const char *fmt, ...) {
            va_list ap;
            va_start(ap, fmt);
            log(Level::DEBUG, category, fmt, ap);
            va_end(ap);
        }

        static void info(Category category, const char *fmt, ...) {
            va_list ap;
            va_start(ap, fmt);
            log(Level::INFO, category, fmt, ap);
            va_end(ap);
        }

        static void warning(Category category, const char *fmt, ...) {
            va_list ap;
            va_start(ap, fmt);
            log(Level::WARN, category, fmt, ap);
            va_end(ap);
        }

        static void error(Category category, const char *fmt, ...) {
            va_list ap;
            va_start(ap, fmt);
            log(Level::ERROR, category, fmt, ap);
            va_end(ap);
        }

        static void fatal(Category category, const char *fmt, ...) {
            va_list ap;
            va_start(ap, fmt);
            log(Level::FATAL, category, fmt, ap);
            va_end(ap);

            std::abort();
        }

    private:
        static void log(Level level, Category category, const char *fmt, va_list ap);

    private:
        static std::map<Category, Level> s_levels;
    };

}

#endif // GZZZT_LOG_H

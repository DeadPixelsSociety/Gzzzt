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
#ifndef GZZZT_CONCURRENT_QUEUE_H
#define GZZZT_CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>

namespace gzzzt {

    template<class T>
    class ConcurrentQueue {
    public:
        bool empty() {
            m_qMutex.lock();
            bool isEmpty = m_queue.empty();
            m_qMutex.unlock();
            return isEmpty;
        }

        T pop() {
            m_qMutex.lock();
            T value = m_queue.front();
            m_qMutex.unlock();
            return value;
        }

        void push(T value) {
            m_qMutex.lock();
            m_queue.push(value);
            m_qMutex.unlock();
        }

    private:
        std::queue<T> m_queue;
        std::mutex m_qMutex;
    };

}

#endif // GZZZT_CONCURRENT_QUEUE_H

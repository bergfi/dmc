/*
 * DMC - DMC Model Checker is a modular, multi-core model checker
 * Copyright © 2021 Freark van der Berg
 *
 * This file is part of DMC.
 *
 * DMC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * DMC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DMC.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <pthread.h>

namespace llmc {

template<typename T>
class TLS {
public:

    TLS() {
        pthread_key_create(&_key, NULL);
    }

    ~TLS() {
        pthread_key_delete(_key);
    }

    void operator=(T* t) {
        pthread_setspecific(_key, t);
    }

    T& operator*() {
        return *(T*) pthread_getspecific(_key);
    }

    T* operator->() {
        return (T*) pthread_getspecific(_key);
    }

    T* get() {
        return (T*) pthread_getspecific(_key);
    }

private:
    pthread_key_t _key;
};

} // namespace llmc
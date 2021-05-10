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

struct TransitionInfoUnExpanded {

    static TransitionInfoUnExpanded None() { return TransitionInfoUnExpanded(0ULL); }

    template<typename T>
    static TransitionInfoUnExpanded construct(T& t) {
        static_assert(sizeof(t) == sizeof(_data));
        return TransitionInfoUnExpanded(*reinterpret_cast<decltype(_data)*>(&t));
    }

    template<typename T>
    T const& get() const {
        return *reinterpret_cast<const T*>(&_data);
    }
private:
    explicit TransitionInfoUnExpanded(size_t data): _data(data) {}
private:
    size_t _data;
};

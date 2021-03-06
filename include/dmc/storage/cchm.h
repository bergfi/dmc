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

#include "interface.h"
#include "chaintableUBVKmem.h"
#include <libfrugi/Settings.h>
#include <thread>

using namespace libfrugi;

namespace chaintablegenericUBVKmem {

template<>
struct key_accessor<llmc::storage::StorageInterface::FullState> {

    __attribute__((always_inline))
    static size_t size(llmc::storage::StorageInterface::FullState const& key) {
//        printf("length %u\n", key.getLengthInBytes());
        return key.getLengthInBytes() + sizeof(llmc::storage::StorageInterface::FullState);
    }
};

}

namespace llmc::storage {

class cchm: public StorageInterface {
public:

    cchm(): _store(24), _rootMap(nullptr), _hashmapScale(24), _hashmapRootScale(24) {

    }

    ~cchm() {
        size_t buckets = 1ULL << _hashmapRootScale;
        if(_rootMap) chaintablegenericUBVKmem::MMapper::munmap(_rootMap, buckets * sizeof(*_rootMap));
        _rootMap = nullptr;
    }

    void init() {
        _store.getSlabManager().setMinimumSlabSize(1ULL << _hashmapScale);
        _store.setBucketScale(_hashmapScale);
        size_t buckets = 1ULL << _hashmapRootScale;
        _hashmapRootMask = buckets - 1;
        _rootMap = (decltype(_rootMap))chaintablegenericUBVKmem::MMapper::mmapForMap(buckets * sizeof(*_rootMap));
        assert(_rootMap);
        _store.init();
    }

    void thread_init() {
        _store.thread_init();
    }

    using StateSlot = StorageInterface::StateSlot;
    using StateID = StorageInterface::StateID;
    using StateTypeID = StorageInterface::StateTypeID;
    using Delta = StorageInterface::Delta;
    using MultiDelta = StorageInterface::MultiDelta;

    StateID find(const FullState* state) {
        chaintablegenericUBVKmem::HashTable<FullState>::HTE* result;
        if(_store.get(*state, result)) {
            return findInRootMap(result) | (state->getLength() << 40);
        }
        return StateID::NotFound();
    }

    StateID find(const StateSlot* state, size_t length, bool isRoot) {
        auto fsd = FullStateData<StateSlot>::createExternal(isRoot, length, state);
        auto r = find(fsd);
        return r;
    }

    uintptr_t findInRootMap(chaintablegenericUBVKmem::HashTable<FullState>::HTE* id) {
        size_t e = ((uintptr_t)id) & _hashmapRootMask;
        while(true) {
            chaintablegenericUBVKmem::HashTable<FullState>::HTE* loaded = _rootMap[e].load(std::memory_order_relaxed);
            if(loaded == id) {
                break;
            }
            if(!loaded) {
                std::atomic_thread_fence(std::memory_order_acquire);
                loaded = _rootMap[e].load(std::memory_order_relaxed);
                if(loaded == id) {
                    break;
                }
            }
            if(!loaded) {
                std::this_thread::yield();
            } else {
                e++;
            }
        }
        return e;
    }

    //    InsertedState insertOverwrite(FullState* state) {
//        auto id = _nextID;
//        auto r = _store.insert_or_assign(state, id);
//        return {r.first->second, r.second};
//    }
//    InsertedState insertOverwrite(StateSlot* state, size_t length, bool isRoot) {
//        return insert(FullStateData<StateSlot>::create(isRoot, length, state));
//    }

    InsertedState insert(const FullState* state) {
        chaintablegenericUBVKmem::HashTable<FullState>::HTE* id = nullptr;
        bool inserted = _store.insert(*state, id);
        size_t e = ((uintptr_t)id) & _hashmapRootMask;
        if(inserted) {
            chaintablegenericUBVKmem::HashTable<FullState>::HTE* nullValue = nullptr;
            while(!_rootMap[e].compare_exchange_strong(nullValue, id, std::memory_order_release, std::memory_order_relaxed)) {
                if(nullValue == id) {
                    break;
                    inserted = false;
                }
                nullValue = nullptr;
                e++;
            }
        } else {
            e = findInRootMap(id);
        }
        return InsertedState(e | (state->getLength() << 40), inserted);
    }

    InsertedState insert(const StateSlot* state, size_t length, bool isRoot) {
        return insert(FullStateData<StateSlot>::createExternal(isRoot, length, state));
    }

    InsertedState insert(StateID const& stateID, Delta const& delta, bool isRoot) {
        return insert(stateID, delta.getOffset(), delta.getLength(), delta.getData(), isRoot);
    }
    InsertedState insert(StateID const& stateID, size_t offset, size_t length, const StateSlot* data, bool isRoot) {
        size_t oldLength = 0;
        size_t newLength = 0;

        StateSlot* buffer;

        if(stateID.getData()) {
            FullState* old = get(stateID, isRoot);
            oldLength = old->getLength();
                    LLMC_DEBUG_ASSERT(old);
                    LLMC_DEBUG_ASSERT(old->getLength());
            newLength = std::max(oldLength, length + offset);
            buffer = (StateSlot*)alloca(newLength * sizeof(StateSlot));
            memcpy(buffer, old->getData(), oldLength * sizeof(StateSlot));
        } else {
            newLength = length + offset;
            buffer = (StateSlot*)alloca(newLength * sizeof(StateSlot));
            memset(buffer, 0, offset * sizeof(StateSlot));
        }
        if(data) {
            memcpy(buffer+offset, data, length * sizeof(StateSlot));
        } else {
            memset(buffer+offset, 0, length * sizeof(StateSlot));
        }
        if(offset > oldLength) {
            memset(buffer+oldLength, 0, (offset - oldLength) * sizeof(StateSlot));
        }

        return insert(buffer, newLength, isRoot);
    }

    InsertedState append(StateID const& stateID, size_t length, const StateSlot* data, bool isRoot) {
        if(!stateID.getData()) {
            return insert(data, length, isRoot);
        }
        FullState* old = get(stateID, isRoot);
        LLMC_DEBUG_ASSERT(old);
        LLMC_DEBUG_ASSERT(old->getLength());

        size_t offset = old->getLength();

//        fprintf(stderr, "old:");
//        for(int i=0; i < old->getLength(); ++i) {
//            fprintf(stderr, " %x", old->getData()[i]);
//        }
//        fprintf(stderr, "\n");

        size_t newLength = std::max(old->getLength(), length + offset);

        StateSlot buffer[newLength];

        memcpy(buffer, old->getData(), old->getLength() * sizeof(StateSlot));
        if(data) {
            memcpy(buffer+offset, data, length * sizeof(StateSlot));
        } else {
            memset(buffer+offset, 0, length * sizeof(StateSlot));
        }
        if(offset > old->getLength()) {
            memset(buffer+old->getLength(), 0, (offset - old->getLength()) * sizeof(StateSlot));
        }
//        fprintf(stderr, "new:");
//        for(int i=0; i < newLength; ++i) {
//            fprintf(stderr, " %x", buffer[i]);
//        }
//        fprintf(stderr, "\n");

        return insert(buffer, newLength, isRoot);

    }

    // need to do:
    // - external FullState
    // - FullState needs to be tailored for treedbs






    FullState* get(StateID id, bool isRoot) {
        assert(id.getData());
//        auto hte = (chaintablegenericUBVKmem::HashTable<FullState>::HTE*)id.getData();
        auto hte = _rootMap[id.getData() & 0xFFFFFFFFFFULL].load(std::memory_order_acquire);
//        FullState* state = (FullState*)&hte->_length;
//        auto state = FullState::createExternal(isRoot, hte->_length / sizeof(StateSlot), (StateSlot*)hte->_keyData);
        FullState& state = hte->get();

        if(state.isRoot() == isRoot) {
            return &state;
        } else {
            return nullptr;
        }
    }

    bool get(StateSlot* dest, StateID stateID, bool isRoot) {
        FullState* s = get(stateID, isRoot);
        if(s) {
            memcpy(dest, s->getData(), s->getLengthInBytes());
        }
        return s != nullptr;
    }

    bool getPartial(StateID stateID, size_t offset, StateSlot* dest, size_t length, bool isRoot) {
        FullState* s = get(stateID, isRoot);
        if(s) {
            memcpy(dest, &s->getData()[offset], length * sizeof(StateSlot));
        }
        return s != nullptr;
    }

    void getPartial(StateID id, MultiProjection& projection, bool isRoot, uint32_t* buffer) {
        abort();
        size_t length = 0;
        for(size_t p = 0; p < projection.getProjections(); ++p) {
            length += projection.getProjection(p).getLengthAndOffsets().getLength();
        }
        memset(buffer, 0, length * sizeof(uint32_t));
    }
    InsertedState delta(StateID idx, MultiProjection& projection, bool isRoot, uint32_t* buffer) {
        abort();
        return InsertedState();
    }

    bool getSparse(StateID stateID, uint32_t* buffer, uint32_t offsets, SparseOffset* offset, bool isRoot) {
        FullState* s = get(stateID, isRoot);
        if(s) {
            SparseOffset* offsetEnd = offset + offsets;
            while(offset < offsetEnd) {
                uint32_t o = offset->getOffset();
                uint32_t l = offset->getLength();
                memcpy(buffer, &s->getData()[o], l * sizeof(StateSlot));
                buffer += l;
                offset++;
            }
            return true;
        }
        return false;
    }

    InsertedState deltaSparse(StateID stateID, uint32_t* delta, uint32_t offsets, SparseOffset* offset, bool isRoot) {
        FullState* old = get(stateID, isRoot);
                LLMC_DEBUG_ASSERT(old);
                LLMC_DEBUG_ASSERT(old->getLength());
        if(old) {
            StateSlot buffer[old->getLength()];
            memcpy(buffer, old->getData(), old->getLength() * sizeof(StateSlot));
            SparseOffset* offsetEnd = offset + offsets;
            while(offset < offsetEnd) {
                uint32_t o = offset->getOffset();
                uint32_t l = offset->getLength();
                memcpy(buffer + o, delta, l * sizeof(StateSlot));
                delta += l;
                offset++;
            }
            return insert(buffer, old->getLength(), isRoot);
        }
        return InsertedState();

    }

    void printStats() {
    }

    static bool constexpr accessToStates() {
        return true;
    }

    static bool constexpr stateHasFixedLength() {
        return false;
    }

    static bool constexpr stateHasLengthInfo() {
        return false;
    }

    static bool constexpr needsThreadInit() {
        return true;
    }

    size_t determineLength(StateID const& s) const {
        return s.getData() >> 40;
//        auto hte = (chaintablegenericUBVKmem::HashTable<FullState>::HTE*)s.getData();
//        return hte->_length;
    }

    size_t getMaxStateLength() const {
        return 1ULL << 32;
    }

    void setSettings(Settings& settings) {
        size_t hashmapScale = settings["storage.cchm.hashmap_scale"].asUnsignedValue();
        hashmapScale = hashmapScale ? hashmapScale : settings["storage.hashmap_scale"].asUnsignedValue();
        if(hashmapScale) {
            _hashmapScale = hashmapScale;
        }

        size_t hashmapRootScale = settings["storage.cchm.hashmaproot_scale"].asUnsignedValue();
        hashmapRootScale = hashmapRootScale ? hashmapRootScale : settings["storage.hashmaproot_scale"].asUnsignedValue();
        hashmapRootScale = hashmapRootScale ? hashmapRootScale : settings["storage.cchm.hashmap_scale"].asUnsignedValue();
        hashmapRootScale = hashmapRootScale ? hashmapRootScale : settings["storage.hashmap_scale"].asUnsignedValue();
        if(hashmapRootScale) {
            _hashmapRootScale = hashmapRootScale;
        }
    }

    Statistics getStatistics() {
        Statistics stats;

        stats._bytesReserved = _store.getSlabManager().max_size();
        stats._bytesInUse = _store.getSlabManager().size();
        stats._bytesMaximum = 0;
        stats._elements = 0;

        decltype(_store)::stats s;
        _store.getStats(s);

        stats._elements = s.size;
        stats._bytesInUse += sizeof(uint64_t) * s.usedBuckets;
        stats._bytesReserved += sizeof(uint64_t) * _store.getBuckets();

        stats._bytesReserved += (1ULL << _hashmapRootScale) * sizeof(*_rootMap);
        std::atomic<chaintablegenericUBVKmem::HashTable<FullState>::HTE*>* e = _rootMap;
        std::atomic<chaintablegenericUBVKmem::HashTable<FullState>::HTE*>* eEnd = e + (1ULL << _hashmapRootScale);
        while(e < eEnd) {
            if(e->load(std::memory_order_relaxed)) {
                stats._bytesInUse += sizeof(*_rootMap);
            }
            e++;
        }

        return stats;
    }

    std::string getName() const {
        return "cchm";
    }

private:
    chaintablegenericUBVKmem::HashTable<FullState, std::hash<FullState>, std::equal_to<FullState>> _store;
    std::atomic<chaintablegenericUBVKmem::HashTable<FullState>::HTE*>* _rootMap;
    size_t _hashmapScale;
    size_t _hashmapRootScale;
    size_t _hashmapRootMask;
};

} // namespace llmc::storage

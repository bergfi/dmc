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

#include <cstring>

#include <dmc/common/assertions.h>
#include <dmc/common/murmurhash.h>

namespace llmc::storage {

template<typename StateSlot>
struct FullStateData {

    static const size_t OFFSET_TYPE = 24;
    static const size_t BITS_TYPE = 8;
    static const size_t MASK_TYPE = ((1ULL << BITS_TYPE) - 1) << OFFSET_TYPE;

    static const size_t MASK_EXTERNALDATA = (1ULL);

    static FullStateData* createExternal(bool isRoot, size_t length, const StateSlot* data) {
        FullStateData* fsd = (FullStateData*)malloc(sizeof(FullStateData));
        fsd->_misc = MASK_EXTERNALDATA;
        fsd->_lengthAndType = length | (((size_t)!isRoot) << OFFSET_TYPE);
        fsd->_externalData = data;
        return fsd;
    }

    static FullStateData* create(bool isRoot, size_t length, const StateSlot* data) {
        FullStateData* fsd = (FullStateData*)malloc(sizeof(_header) + length * sizeof(StateSlot));
        fsd->_misc = 0;
        fsd->_lengthAndType = length | (((size_t)!isRoot) << OFFSET_TYPE);
        memcpy(fsd->_data, data, length * sizeof(StateSlot));
        return fsd;
    }

    static FullStateData* create(bool isRoot, size_t length) {
        FullStateData* fsd = (FullStateData*)malloc(sizeof(_header) + length * sizeof(StateSlot));
        fsd->_misc = 0;
        fsd->_lengthAndType = length | (((size_t)!isRoot) << OFFSET_TYPE);
        return fsd;
    }

    static FullStateData* create(FullStateData* fsd, bool isRoot, size_t length) {
        fsd->_misc = 0;
        fsd->_lengthAndType = length | (((size_t)!isRoot) << OFFSET_TYPE);
        return fsd;
    }

    void destroy() {
        if((this->_misc & MASK_EXTERNALDATA) == 0) {
            free(this);
        }
    }

    size_t getType() const {
        return _lengthAndType >> OFFSET_TYPE;
    }

    size_t getLength() const {
        return _lengthAndType & 0xFFFFFFULL;
    }

    size_t getLengthInBytes() const {
        return getLength() * sizeof(StateSlot);
    }

    const StateSlot* getData() const {
        return _misc & MASK_EXTERNALDATA ? _externalData : _data;
    }

    const char* getCharData() const {
        return (char*)getData();
    }

    StateSlot* getDataToModify() {
        assert(!(_misc & MASK_EXTERNALDATA));
        return _data;
    }

    bool isRoot() const {
        return !(_lengthAndType & MASK_TYPE);
    }

    bool equals(FullStateData const& other) const {
        if(_lengthAndType != other._lengthAndType) return false;

        auto thisData = _misc & MASK_EXTERNALDATA ? (void*)_externalData : (void*)_data;
        auto otherData = other._misc & MASK_EXTERNALDATA ? (void*)other._externalData : (void*)other._data;

        auto r = !memcmp(thisData, otherData, getLength() * sizeof(StateSlot));
//        LLMC_DEBUG_LOG() << "Compared " << *this << " to " << other << ": " << r << std::endl;
        return r;
    }

    size_t hash() const {
        return _lengthAndType ^ MurmurHash64(_misc & MASK_EXTERNALDATA ? _externalData : _data, getLength(), 0);
    }

    friend std::ostream& operator<<(std::ostream& os, FullStateData<StateSlot> const& fsd) {
        os << "[";
        os << fsd.getLength();
        os << ",";
        os << fsd.hash();
        os << ",";
        const StateSlot* s = fsd.getData();
        const StateSlot* end = s + fsd.getLength();
        for(; s < end; s++) {
            os << std::hex << " " << *s;
        }
        os << "]" << std::endl;
        return os;
    }

    FullStateData const& operator=(FullStateData const& other) {
        _header = other._header;
        if(_misc & MASK_EXTERNALDATA) {
            _misc &= ~MASK_EXTERNALDATA;
            memcpy(_data, other._externalData, getLengthInBytes());
        } else {
            memcpy(_data, other._data, getLengthInBytes());
        }
        return *this;
    }

private:
    union {
        struct {
            uint32_t _lengthAndType; // in nr of StateSlots
            uint32_t _misc;
        };
        size_t _header;
    };
    union {
        StateSlot _data[0];
        const StateSlot* _externalData;
    };
};

//static_assert(sizeof(FullStateData<unsigned int>) == sizeof(size_t));

class StorageInterface {
public:

    using StateSlot = uint32_t;
    //using StateID = uint64_t;
    using StateTypeID = uint16_t;
    using FullState = FullStateData<StateSlot>;

    /**
     * 8b: length
     * 24b: offset
     */
    struct SparseOffset {

    public:
        constexpr SparseOffset(uint32_t const& offset, uint32_t const& length): _data((offset << 8) | length) {
//            assert(length < 256);
        }
        constexpr SparseOffset(uint32_t const& data): _data(data) {}
        constexpr SparseOffset(): _data(0) {}
    public:

        uint32_t getOffset() const {
            return _data >> 8;
        }

        uint32_t getLength() const {
            return _data & 0xFF;
        }

        uint32_t getOffsetPart() const {
            return _data & 0xFF000000;
        }

        uint32_t _data;
    };

    struct MultiOffset {

    public:
        enum class Options {
            NONE,
            READ,
            WRITE,
            READ_WRITE
        };
    public:
        __attribute__((always_inline))
        constexpr MultiOffset(uint32_t const& offset, uint32_t const& options): _data(offset | (options << 24)) {}

        __attribute__((always_inline))
        constexpr MultiOffset(uint32_t const& data): _data(data) {}

        __attribute__((always_inline))
        constexpr MultiOffset(): _data(0) {}
    public:

        __attribute__((always_inline))
        void init(uint32_t const& offset, Options const& options) {
            _data = offset | ((uint32_t)options << 24);
        }

        __attribute__((always_inline))
        uint32_t getOffset() const {
            return _data & 0xFFFFFF;
        }

        __attribute__((always_inline))
        Options getOptions() const {
            return (Options)(_data >> 24);
        }

        __attribute__((always_inline))
        bool operator<(SparseOffset const& other) {
            return _data < other._data;
        }

        __attribute__((always_inline))
        uint32_t getData() const {
            return _data;
        }

        uint32_t _data;
    };

    struct LengthAndOffset: private MultiOffset {
    public:
        __attribute__((always_inline))
        constexpr LengthAndOffset(uint32_t const& length, uint32_t const& offsets): MultiOffset(length, offsets) {}

        __attribute__((always_inline))
        constexpr LengthAndOffset(uint32_t const& data): MultiOffset(data) {}

        __attribute__((always_inline))
        constexpr LengthAndOffset(): MultiOffset() {}
    public:

        __attribute__((always_inline))
        void init(uint32_t const& length, uint32_t const& offsets) {
            this->_data = length | (offsets << 24);
        }

        __attribute__((always_inline))
        uint32_t getLength() const {
            return this->_data & 0xFFFFFF;
        }

        __attribute__((always_inline))
        uint32_t getOffsets() const {
            return this->_data >> 24;
        }
    };

    struct Projection {
    public:
        constexpr Projection(SparseOffset* const& offsets): _offsets(offsets) {}
    public:

        SparseOffset* getOffsets() const {
            return _offsets;
        }

        SparseOffset* _offsets;
    };

    struct MultiProjection {
    public:

        struct SingleProjection {

            SingleProjection() {}

            SingleProjection(MultiOffset::Options options, uint32_t length, std::initializer_list<uint32_t> offsets) {
                int i = 0;
                for(auto& o: offsets) {
                    _data[i++].init(o, options);
                }
                lando.init(length, i); // TODO: determine if we want nr of offsets or stride
            }

            typename MultiOffset::Options getOptions() const {
                return _data[0].getOptions();
            }

            LengthAndOffset getLengthAndOffsets() const {
                return lando;
            }

            MultiOffset* getOffsets() {
                return _data;
            }

            MultiOffset& getOffset(uint32_t level) {
                return _data[level];
            }

            uint32_t getLength(uint32_t level) const {
                LengthAndOffset& lando = ((LengthAndOffset&)_data[0]);
                return level < lando.getOffsets() - 1 ? 2 : lando.getLength();
            }

            LengthAndOffset lando;
            MultiOffset _data[];
        };
    public:

        static size_t getRequiredBufferSize32B(uint32_t maxProjections, uint32_t maxDepth) {
            return sizeof(MultiProjection)/sizeof(uint32_t) + maxProjections * maxDepth;
        }

        static MultiProjection& create(uint32_t* buffer, uint32_t maxProjections, uint32_t maxDepth) {
            MultiProjection* projection = (MultiProjection*)buffer;
            projection->projections = 0;
            projection->maxProjections = maxProjections;
            projection->maxDepth = maxDepth;
            return *projection;
        }

        size_t getProjections() const {
            return projections;
        }

        size_t getStride() const {
            return maxDepth + 1;
        }

        SingleProjection& getProjection(size_t idx) {
            return *(SingleProjection*)&_projections[idx * getStride()];
        }

        void addProjection(MultiOffset::Options options, uint32_t length, std::initializer_list<uint32_t> offsets) {
            assert(projections < maxProjections);
            new(&getProjection(projections)) SingleProjection(options, length, offsets);
            projections++;
        }

        uint32_t projections;
        uint32_t maxProjections;
        uint32_t maxDepth;
        uint32_t _projections[];
    };

    struct StateID64 {
    public:
        constexpr StateID64(): _data(0) {}

        constexpr StateID64(uint64_t const& d): _data(d) {}
        bool exists() const {
            return _data != 0;
        }

        constexpr uint64_t getData() const {
            return _data;
        }

        static constexpr StateID64 NotFound() {
            return StateID64(0);
        }

        constexpr bool operator==(StateID64 const& other) const {
            return _data == other._data;
        }

        constexpr bool operator!=(StateID64 const& other) const {
            return _data != other._data;
        }

        friend std::ostream& operator<<(std::ostream& os, StateID64 const& state) {
            os << "(" << std::hex << state.getData() << ")";
            return os;
        }
    protected:
        uint64_t _data;

    };

    struct StateID32 {
    public:
        constexpr StateID32(): _data(0) {}

        constexpr StateID32(uint32_t const& d): _data(d) {}
        constexpr StateID32(int32_t const& d): _data((uint32_t)d) {}
        constexpr StateID32(uint64_t const& d): _data(d) {
            assert(d == _data);
        }
        constexpr StateID32(int64_t const& d): _data((uint32_t)d) {
            assert(d == _data);
        }
        bool exists() const {
            return _data != 0;
        }

        constexpr uint32_t getData() const {
            return _data;
        }

        static constexpr StateID32 NotFound() {
            return StateID32((uint32_t)0);
        }

        constexpr bool operator==(StateID32 const& other) const {
            return _data == other._data;
        }

        constexpr bool operator!=(StateID32 const& other) const {
            return _data != other._data;
        }

        friend std::ostream& operator<<(std::ostream& os, StateID32 const& state) {
            os << "(" << std::hex << state.getData() << ")";
            return os;
        }
    protected:
        uint32_t _data;

    };

    using StateID = StateID64;

    class InsertedState {
    public:

        InsertedState(): _stateID(0), _inserted(0) {}

        InsertedState(StateID stateId, bool inserted): _stateID(stateId), _inserted(inserted) {}

        StateID getState() const {
            return _stateID;
        }

        bool isInserted() const {
            return _inserted;
        }
        friend std::ostream& operator<<(std::ostream& os, InsertedState const& insertedState) {
            os << insertedState.getState() << (insertedState.isInserted() ? "+" : "");
            return os;
        }
    private:
        StateID _stateID;
        uint64_t _inserted;
    };

    struct Delta {

        static Delta& create(void* buffer, size_t offset, const StateSlot* data, size_t len) {
            Delta* delta = (Delta*)buffer;
            delta->_offset = offset;
            delta->_length = len;
            memcpy(delta->_data, data, len * sizeof(StateSlot));
            return *delta;
        }

        static Delta* create(size_t offset, const StateSlot* data, size_t len) {
            Delta* d = (Delta*)malloc(sizeof(Delta) + len * sizeof(StateSlot));
            create(d, offset, data, len);
            return d;
        }

        static Delta& create(Delta* buffer, size_t offset, size_t len) {
            return Delta::create(buffer, offset, buffer->_data, len);
        }

        static void destroy(Delta* d) {
            free(d);
        }

        size_t getOffset() const {
            return _offset;
        }

        size_t getLength() const {
            return _length;
        }

        size_t getOffsetInBytes() const {
            return getOffset() * sizeof(StateSlot);
        }

        size_t getLengthInBytes() const {
            return getLength() * sizeof(StateSlot);
        }

        const StateSlot* getData() const {
            return _data;
        }

    private:
        size_t _offset;
        size_t _length;
        StateSlot _data[];
    };

    struct MultiDelta {
        size_t length;
    };

//    StateID find(FullState* state);
//    StateID find(StateSlot* state, size_t length, bool isRoot);
////    InsertedState insertOverwrite(FullState* state);
////    InsertedState insertOverwrite(StateSlot* state, size_t length, bool isRoot);
//    InsertedState insert(FullState* state);
//    InsertedState insert(StateSlot* state, size_t length, bool isRoot);
//    InsertedState insert(StateID const& stateID, Delta const& delta);
//    FullState* get(StateID id);
//    FullState* get(StateID id, size_t offset, StateSlot* data, size_t length);
//    void printStats();
};

class Statistics {
public:
    size_t getElements() const {
        return _elements;
    }

    void setElements(size_t elements) {
        _elements = elements;
    }

    size_t getBytesInUse() const {
        return _bytesInUse;
    }

    void setBytesInUse(size_t bytesInUse) {
        _bytesInUse = bytesInUse;
    }

    size_t getBytesReserved() const {
        return _bytesReserved;
    }

    void setBytesReserved(size_t bytesReserved) {
        _bytesReserved = bytesReserved;
    }

    size_t getBytesMaximum() const {
        return _bytesMaximum;
    }

    void setBytesMaximum(size_t bytesMaximum) {
        _bytesMaximum = bytesMaximum;
    }

    Statistics& operator+=(Statistics const& other) {
        _elements += other._elements;
        _bytesInUse += other._bytesInUse;
        _bytesReserved += other._bytesReserved;
        _bytesMaximum += other._bytesMaximum;
        return *this;
    }

public:
    size_t _elements;
    size_t _bytesInUse;
    size_t _bytesReserved;
    size_t _bytesMaximum;
};

} // namespace llmc::storage

namespace std {

template <typename StateSlot>
struct hash<llmc::storage::FullStateData<StateSlot>*>
{
    std::size_t operator()(llmc::storage::FullStateData<StateSlot>* const& fsd) const {
        return fsd->hash();
    }
};

template <typename StateSlot>
struct equal_to<llmc::storage::FullStateData<StateSlot>*> {
    constexpr bool operator()( llmc::storage::FullStateData<StateSlot>* const& lhs, llmc::storage::FullStateData<StateSlot>* const& rhs ) const {
        return lhs->equals(*rhs);
    }
};

template <typename StateSlot>
struct hash<llmc::storage::FullStateData<StateSlot>>
{
    std::size_t operator()(llmc::storage::FullStateData<StateSlot> const& fsd) const {
        return fsd.hash();
    }
};

template <typename StateSlot>
struct equal_to<llmc::storage::FullStateData<StateSlot>> {
    constexpr bool operator()( llmc::storage::FullStateData<StateSlot> const& lhs, llmc::storage::FullStateData<StateSlot> const& rhs ) const {
        return lhs.equals(rhs);
    }
};

template<>
struct hash<llmc::storage::StorageInterface::StateID>
{
    std::size_t operator()(llmc::storage::StorageInterface::StateID const& s) const {
        return std::hash<uint64_t>()(s.getData());
    }
};

template<>
struct equal_to<llmc::storage::StorageInterface::StateID> {
    constexpr bool operator()( llmc::storage::StorageInterface::StateID const& lhs, llmc::storage::StorageInterface::StateID const& rhs ) const {
        return lhs.getData() == rhs.getData();
    }
};

//template <typename StateSlot>
//ostream& operator<<(ostream& os, llmc::storage::FullStateData<StateSlot> const& fsd) {
//    os << "[";
//    os << fsd.getLength();
//    os << ",";
//    os << fsd.hash();
//    os << ",";
//    const StateSlot* s = fsd.getData();
//    const StateSlot* end = s + fsd.getLength();
//    for(; s < end; s++) {
//        os << s;
//    }
//    os << "]" << std::endl;
//    return os;
//}

}
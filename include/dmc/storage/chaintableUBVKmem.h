#pragma once

#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <new>

#include <libfrugi/Settings.h>

using namespace libfrugi;

namespace chaintablegenericUBVKmem {

struct slab {
    char* entries;
    char* nextentry;
    char* end;
    slab* next;

    slab(slab* next, size_t bytesNeeded): next(next) {
        size_t map_page_size = 18 << MAP_HUGE_SHIFT;
        entries = nextentry = (char*)mmap(nullptr, bytesNeeded, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | map_page_size, -1, 0);
        if((intptr_t)entries & 0xFFFF000000000000ULL) {
            std::cout << "Warning: allocated memory slab using upper 16 bits" << std::endl;
        }
//        std::cout << "Allocated slab of " << bytesNeeded << " bytes" << std::endl;
        assert(entries);
        end = entries + bytesNeeded;
    }

    ~slab() {
        munmap(entries, (end-entries));
    }

    template<typename T>
    __attribute__((always_inline))
    T* alloc() {
        return (T*)alloc<sizeof(T)>(sizeof(T));
    }

    __attribute__((always_inline))
    char* alloc(size_t size) {
        auto mem = nextentry;
        nextentry += size;
        return mem;
    }

//    __attribute__((always_inline))
//    char* alloc(size_t size, size_t alignBytes) {
//        auto mem = nextentry;
//        auto al = (intptr_t)mem % alignBytes;
//        if(al) {
//            mem += alignBytes-al;
//        }
//        nextentry = mem + size;
//        return mem;
//    }

    template<int alignPowerTwo>
    __attribute__((always_inline))
    char* alloc(size_t size) {
        auto mem = nextentry;
        mem += alignPowerTwo-1;
        mem = (char*)(((uintptr_t)mem) & ~(alignPowerTwo-1));
        nextentry = mem + size;
        return mem;
    }

    template<typename T>
    __attribute__((always_inline))
    void free(T* mem) {
        return free((void*)mem, sizeof(T));
    }

    __attribute__((always_inline))
    void free(void* mem, size_t length) {
        (void)mem;
        nextentry -= length;
        assert((char*)mem == nextentry);
    }

    size_t size() const {
        return nextentry - entries;
    }

    size_t max_size() const {
        return end - entries;
    }
};

template<typename T>
class slaballocator: public slab  {
public:

    using value_type = T;

    slaballocator(): slab(nullptr, 1ULL<<34ULL) {
    }

    __attribute__((always_inline))
    T* allocate(size_t n) {
        printf("allocate %zu\n", n); fflush(stdout);
        return (T*)alloc<sizeof(T)>(n);
    }

    __attribute__((always_inline))
    void deallocate(T* p, size_t n) {
        (void)p;
        (void)n;
        //return free(p);
    }
};

template<typename T>
class bla {
protected:
    static __thread slab* _slab;
};

template <typename T>
__thread slab* bla<T>::_slab;

class SlabManager: public bla<size_t> {
public:

    SlabManager(size_t minimumSlabSize = 1ULL << 24)
            : _allSlabs(nullptr), _minimumSlabSize(minimumSlabSize)
    {
        Settings& settings = Settings::global();
        _minimumSlabSize = 1ULL << (settings["buckets_scale"].asUnsignedValue()+2);
//        std::cout << this << " SlabManager " << inUse() << std::endl;
    }

    ~SlabManager() {
//        std::cout << this << " ~SlabManager " << inUse() << std::endl;
        auto current = _allSlabs.load(std::memory_order_relaxed);
        while(current) {
            auto next = current->next;
            delete current;
            current = next;
        }
    }

    void setMinimumSlabSize(size_t minimumSlabSize) {
        _minimumSlabSize = minimumSlabSize;
    }

    template<typename T>
    __attribute__((always_inline))
    T* alloc() {
        slab* mySlab = _slab;
        if(mySlab->nextentry + sizeof(T) > mySlab->end) {
            mySlab = linkNewSlab(sizeof(T));
            _slab = mySlab;
        }
        auto r = mySlab->alloc<T>();
        assert(r);
        return r;
    }

    template<typename T>
    __attribute__((always_inline))
    void free(T* mem) {
        return _slab->free(mem);
    }

    template<int alignPowerTwo>
    __attribute__((always_inline))
    char* alloc(size_t size) {
        slab* mySlab = ensureSlab(size);
        auto r = mySlab->alloc<alignPowerTwo>(size);
        assert(r);
        return r;
    }

    __attribute__((always_inline))
    void free(void* mem, size_t length) {
        return _slab->free(mem, length);
    }

    __attribute__((always_inline))
    slab* ensureSlab(size_t size) {
        slab* mySlab = _slab;
        if(mySlab == nullptr || mySlab->nextentry + size > mySlab->end) {
//            slab* oldSlab = mySlab;
            mySlab = linkNewSlab(size);
            _slab = mySlab;
//            std::cout << "new slab " << mySlab << ", old slab " << oldSlab << std::endl;
        }
        return mySlab;
    }

    slab* linkNewSlab(size_t minimum_size) {
        //assert(!_slab.get());
        auto mySlab = new slab(_allSlabs.load(std::memory_order_relaxed), std::max(_minimumSlabSize, minimum_size));
        _slab = mySlab;
        while(!_allSlabs.compare_exchange_weak(mySlab->next, mySlab, std::memory_order_release, std::memory_order_relaxed)) {
        }
        return mySlab;
    }

    __attribute__((always_inline))
    void thread_init() {
        linkNewSlab(0);
    }

    __attribute__((always_inline))
    bool inUse() const {
        return _allSlabs != nullptr;
    }

    size_t size() const {
        size_t size = 0;
        auto current = _allSlabs.load(std::memory_order_relaxed);
        while(current) {
            size += current->size();
            current = current->next;
        }
        return size;
    }

    size_t max_size() const {
        size_t size = 0;
        auto current = _allSlabs.load(std::memory_order_relaxed);
        while(current) {
            size += current->max_size();
            current = current->next;
        }
        return size;
    }

private:
//    static TLS<slab> _slab;
    std::atomic<slab*> _allSlabs;
    size_t _minimumSlabSize;
};

template<typename T>
class SlabPerThreadAllocator {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<class U> struct rebind {
        typedef SlabPerThreadAllocator<U> other;
    };

    SlabPerThreadAllocator() {
    }

    SlabPerThreadAllocator(const SlabPerThreadAllocator<T>& other) throw() {
        assert(!other.inUse());
    }

    template<typename U> SlabPerThreadAllocator(const SlabPerThreadAllocator<U>& other) throw() {
        assert(!other.inUse());
    }

    template<typename U> SlabPerThreadAllocator(SlabPerThreadAllocator<U>&& other) throw() {
        assert(!other.inUse());
    }

    void operator=(const SlabPerThreadAllocator<T>& other) {
        assert(!other.inUse());
    }

    void operator=(SlabPerThreadAllocator<T>&& other) {
        assert(!other.inUse());
    }

    void destroy(pointer p) {
        ((T*)p)->~T();
    }

    void deallocate(pointer p, size_type n) {
        (void)p;
        (void)n;
    }

    pointer allocate(size_type n, const void* /*hint*/ =0 ) {
        size_t bytes = n*sizeof(T);
        char* r = sm.alloc<16>(bytes);
//        std::cout << "allocate << " << bytes << ": " << (void*)r << " - " << (void*)(r+bytes) << std::endl;
        return (pointer)r;
    }

    size_t size() const {
        return sm.size();
    }

    size_t max_size() const {
        return sm.max_size();
    }

    bool inUse() const {
        return sm.inUse();
    }
private:
    SlabManager sm;
};

template<typename T>
class StatelessSlabPerThreadAllocator {
public:
    static SlabPerThreadAllocator<T> allocator;

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<class U> struct rebind {
        typedef StatelessSlabPerThreadAllocator<U> other;
    };

    StatelessSlabPerThreadAllocator() {
    }

    StatelessSlabPerThreadAllocator(const StatelessSlabPerThreadAllocator<T>& other) throw() {
        assert(!other.inUse());
    }

    template<typename U> StatelessSlabPerThreadAllocator(const StatelessSlabPerThreadAllocator<U>& other) throw() {
        assert(!other.inUse());
    }

    template<typename U> StatelessSlabPerThreadAllocator(StatelessSlabPerThreadAllocator<U>&& other) throw() {
        assert(!other.inUse());
    }

    void operator=(const StatelessSlabPerThreadAllocator<T>& other) {
        assert(!other.inUse());
    }

    void operator=(StatelessSlabPerThreadAllocator<T>&& other) {
        assert(!other.inUse());
    }

    void destroy(pointer p) {
        allocator.destroy(p);
    }

    void deallocate(pointer p, size_type n) {
        allocator.deallocate(p, n);
    }

    pointer allocate(size_type n, const void* hint =0 ) {
        allocator.allocate(n, hint);
    }

    size_t size() const {
        return allocator.size();
    }

    size_t max_size() const {
        return allocator.max_size();
    }

    bool inUse() const {
        return allocator.inUse();
    }
};

template<typename T>
SlabPerThreadAllocator<T> StatelessSlabPerThreadAllocator<T>::allocator;

template<typename KEY>
struct key_accessor {

    __attribute__((always_inline))
    static const char* data(KEY const& key) {
        return (const char*)&key;
    }

    __attribute__((always_inline))
    static size_t size(KEY const& key) {
        return sizeof(KEY);
    }
};

class MMapper {
public:
    static void* mmap(size_t bytesNeeded, size_t pageSizePower) {
        size_t page_size = 1ULL << pageSizePower;
        size_t numberOfPages = bytesNeeded / page_size;
        if(numberOfPages > 1ULL) {
        } else {
            numberOfPages = 1ULL;
        }
        size_t map_page_size = pageSizePower << MAP_HUGE_SHIFT;
        auto map = ::mmap(nullptr, bytesNeeded, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | map_page_size, -1, 0);
        std::cout << "MMapped " << bytesNeeded << " bytes, page size " << pageSizePower << " -> " << map << std::endl;
        return map;
    }

    static void* mmapForMap(size_t bytesNeeded) {
        auto map = MMapper::mmap(bytesNeeded, Settings::global()["page_size_scale"].asUnsignedValue());
        posix_madvise(map, bytesNeeded, POSIX_MADV_RANDOM);
        return map;
    }

    static void* mmapForBucket() {
        size_t bytesNeeded = 1 << 2;
        auto map = ::mmap(nullptr, bytesNeeded, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
        posix_madvise(map, bytesNeeded, POSIX_MADV_SEQUENTIAL);
        return map;
    }

    static void munmap(void* addr, size_t len) {
        ::munmap(addr, len);
    }
};

template<typename K>
class HashTableEntry {
public:

    HashTableEntry(size_t length, const char* keyData, HashTableEntry* next): _length(length), _next(next) {
        memcpy(_keyData, keyData, length);
    }

    HashTableEntry(size_t length, K const& key, HashTableEntry* next): _length(length), _next(next) {
        *(K*)_keyData = key;
    }

    K& get() const {
        return *((K*)_keyData);
    }

    HashTableEntry* getNext() {
        return _next.load(std::memory_order_relaxed);
    }
    void setNext(HashTableEntry* next) {
        _next.store(next, std::memory_order_relaxed);
    }

    size_t size() const {
        return sizeof(HashTableEntry) + _length;
    }

//    bool matches(size_t length, const char* keyData) const {
//        if( _length != length) return false;
//        return !memcmp(_keyData, keyData, length);
//    }

public:
    size_t _length;
    std::atomic<HashTableEntry*> _next;
    char _keyData[0];
};

template<typename K, typename Hash=std::hash<K>, typename KeyEqual=std::equal_to<K>>
class HashTable {
public:
    static constexpr size_t PAGE_SIZE_P2 = 20;
public:


    using HTE = HashTableEntry<K>;
    using V = HTE*;

    HashTable()
            : _buckets(0)
            , _map(nullptr)
    {
    }

    HashTable(size_t bucketsScale)
            : _buckets(1ULL << bucketsScale)
            , _map(nullptr)
    {
    }
public:

    void init() {
        _map = (decltype(_map))MMapper::mmapForMap(_buckets * sizeof(std::atomic<HTE*>));
    }

    bool insert(K const& key, V& value) {
//        printf("key:   %zx\n", key);
        size_t h = Hash()(key);
//        printf("hash: %zx\n", h);
        size_t h16l = hash16LeftFromHash(h);
        size_t e = entryFromhash(h);
//        printf("entry: %zu, %zu\n", e, _buckets);
        HTE* current = _map[e].load(std::memory_order_relaxed);
//        printf("cur:   %p\n", current);

//        const char* keyData = chaintablegenericUBVKmem::key_accessor<K>::data(key);
        size_t length = chaintablegenericUBVKmem::key_accessor<K>::size(key);

        std::atomic<HTE*>* parentLink = &_map[e];
        while(current) {
//            printf("checking existing entry: %zx -> %zx\n", current->_key, current->_value);
            size_t currentHash = ((intptr_t)current & 0xFFFF000000000000ULL);
            current = (HTE*)((intptr_t)current & 0x0000FFFFFFFFFFFFULL);
            if(currentHash == h16l) {
                if(KeyEqual()(current->get(), key)) {
                    value = current;
                    return false;
                }
            }
            parentLink = &(current->_next);
            current = current->getNext();
        }

        HTE* hte = createHTE(length, key, nullptr);
        HTE* hteWithHash = (HTE*)(((intptr_t)hte)|h16l);
        while(!parentLink->compare_exchange_weak(current, hteWithHash, std::memory_order_release, std::memory_order_relaxed)) {
            while(current) {
                size_t currentHash = ((intptr_t)current & 0xFFFF000000000000ULL);
                current = (HTE*)((intptr_t)current & 0x0000FFFFFFFFFFFFULL);
                if(currentHash == h16l) {
                    if(KeyEqual()(current->get(), key)) {
                        //delete hte;
                        value = current;
                        return false;
                    }
                }
                parentLink = &current->_next;
                current = current->getNext();
            }
        }
//        std::cout << "Inserted " << hte << " @ [" << e << "] ";
//        printHex(keyData, length);
//        std::cout << ") -> " << value << ", h=" << h << ", hash16l=" << h16l << std::endl;

        value = hte;
        return true;
    }

    bool get(K const& key, V& value) {
        size_t h = Hash()(key);
        size_t h16l = hash16LeftFromHash(h);
        size_t e = entryFromhash(h);
//        printf("entry: %zx\n", e);
        HTE* current = _map[e].load(std::memory_order_relaxed);
//        printf("cur:   %p\n", current);
//        size_t length = chaintablegenericUBVKmem::key_accessor<K>::size(key);

        while(current) {
//            printf("checking existing entry: %zx -> %zx\n", current->_key, current->_value);
            size_t currentHash = ((intptr_t)current & 0xFFFF000000000000ULL);
            current = (HTE*)((intptr_t)current & 0x0000FFFFFFFFFFFFULL);
            if(currentHash == h16l) {
                if(KeyEqual()(current->get(), key)) {
                    value = current;
                    return true;
                }
            }
            current = current->getNext();
        }

        return false;
//        return get2(key, value);
    }

    void printHex(const char* key, size_t length) {
        for(size_t i = 0; i < length; ++i) {
            printf(" %X", ((const unsigned char*)key)[i] & 0xFF);
        }
    }

    bool get2(K const& key, V& value) {
        size_t h = Hash()(key);
        size_t h16l = hash16LeftFromHash(h);
        size_t e = entryFromhash(h);
        HTE* current = _map[e].load(std::memory_order_relaxed);

//        const char* keyData = chaintablegenericUBVKmem::key_accessor<K>::data(key);
//        size_t length = chaintablegenericUBVKmem::key_accessor<K>::size(key);

        std::cout << "==== Looking for entry: ";
//        printHex(keyData, length);
        std::cout << ", h=" << h
                  << ", hash16l=" << h16l
                  << ", e=" << e
                  << std::endl;

        while(current) {
            size_t currentHash = ((intptr_t)current & 0xFFFF000000000000ULL);
            std::cout << "Checking entry " << current << ", hash " << currentHash << std::endl;
            current = (HTE*)((intptr_t)current & 0x0000FFFFFFFFFFFFULL);
            if(currentHash == h16l) {
                std::cout << "  Key/Value: (";
                printHex(current->_keyData, current->_length);
                std::cout << ") -> " << current->_value << std::endl;
                if(KeyEqual()(current->get(), key)) {
                    value = current->_value;
                    std::cout << "    Match." << std::endl;
                    return true;
                }
            }
            current = current->getNext();
        }

        return false;
    }

    size_t hash16LeftFromHash(size_t h) const {
//        h ^= h << 32ULL;
//        h ^= h << 16ULL;
        return h & 0xFFFF000000000000ULL;
    }

    size_t entryFromhash(size_t const& h) {
        return h & (_buckets-1);
    }

//    size_t hash(K const& key) {
//        const char* keyData = chaintablegenericUBVKmem::key_accessor<K>::data(key);
//        size_t length = chaintablegenericUBVKmem::key_accessor<K>::size(key);
//        return MurmurHash64(keyData, length, 0);
//    }

    size_t bucketSize(std::atomic<HTE*>* bucket) {
        size_t s = 0;
        HTE* current = bucket->load(std::memory_order_relaxed);
        while(current) {
            s++;
            current = (HTE*)((intptr_t)current & 0x0000FFFFFFFFFFFFULL);
            current = current->getNext();
        }
        return s;
    }

    size_t size() {
        size_t s = 0;
        std::atomic<HTE*>* bucket = _map;
        std::atomic<HTE*>* end = _map + _buckets;
        while(bucket < end) {
            s += bucketSize(bucket);
            bucket++;
        }
        return s;
    }

    void printStatistics() {
        printf("ht stats\n");
        printf("size = %zu\n", size());
    }

    void thread_init() {
        _slabManager.thread_init();
    }

    HTE* createHTE(size_t length, K const& key, HTE* next) {
        HTE* hte = new(_slabManager.alloc<4>(sizeof(HTE) + length)) HTE(length, key, next);
        assert( (((intptr_t)hte)&0x3) == 0);
        return hte;
    }

    template<typename T>
    void giveMemoryBack(T* const& hte) {
        return _slabManager.free(hte);
    }

    ~HashTable() {
        munmap(_map, _buckets * sizeof(std::atomic<HTE*>));
    }

    struct stats {
        size_t size;
        size_t usedBuckets;
        size_t collisions;
        size_t longestChain;
        double avgChainLength;
    };

    void getStats(stats& s) {
        s.size = 0;
        s.usedBuckets = 0;
        s.collisions = 0;
        s.longestChain = 0;
        s.avgChainLength = 0.0;

        for(size_t idx = 0; idx < _buckets; ++idx) {
            HTE* bucket = _map[idx].load(std::memory_order_relaxed);
            if(bucket) {
                HTE* entry = bucket;
                size_t chainSize = 0;
                while(entry) {
                    chainSize++;
                    entry = (HTE*)((intptr_t)entry & 0x0000FFFFFFFFFFFFULL);
                    entry = entry->_next.load(std::memory_order_relaxed);
                }
                s.usedBuckets++;
                s.size += chainSize;
                s.collisions += chainSize - 1;
                if(chainSize > s.longestChain) s.longestChain = chainSize;
            }
        }
        if(_buckets > 0) {
            s.avgChainLength = (double)s.size / (double)_buckets;
        }
    }

    template<typename CONTAINER>
    void getDensityStats(size_t bars, CONTAINER& elements) {

        size_t bucketPerBar = _buckets / bars;
        bucketPerBar += bucketPerBar == 0;

        for(size_t idx = 0; idx < _buckets;) {
            size_t elementsInThisBar = 0;
            size_t max = std::min(_buckets, idx + bucketPerBar);
            for(; idx < max; ++idx) {

                HTE* bucket = _map[idx].load(std::memory_order_relaxed);
                if(bucket) {
                    HTE* entry = bucket;
                    size_t chainSize = 0;
                    while(entry) {
                        chainSize++;
                        entry = (HTE*)((intptr_t)entry & 0x0000FFFFFFFFFFFFULL);
                        entry = entry->_next.load(std::memory_order_relaxed);
                    }
                    elementsInThisBar += chainSize;
                }
            }
            elements.push_back(elementsInThisBar);
        }

    }

    std::atomic<HTE*>* const getMapLocation() const {
        return _map;
    }

    SlabManager const& getSlabManager() const {
        return _slabManager;
    }

    SlabManager& getSlabManager() {
        return _slabManager;
    }

    void setBucketScale(size_t scale) {
        assert(!_map);
        _buckets = 1ULL << scale;
    }

    size_t getBuckets() const {
        return _buckets;
    }

private:
    size_t _buckets;
    std::atomic<HTE*>* _map;

    SlabManager _slabManager;
};

}

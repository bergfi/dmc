#include <cassert>

extern "C" {

#include "common.h"
#include "config.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "murmurhash.h"

//#define CACHE_LINE 6
//#define CACHE_LINE_SIZE 64

#include <sys/mman.h>
//#include <hre/user.h>
//#include <mc-lib/atomics.h>

uint64_t MurmurHash64 (const void * key, int len, uint64_t seed)
{
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8);

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
        case 7: h ^= ((uint64_t)data2[6]) << 48;
        case 6: h ^= ((uint64_t)data2[5]) << 40;
        case 5: h ^= ((uint64_t)data2[4]) << 32;
        case 4: h ^= ((uint64_t)data2[3]) << 24;
        case 3: h ^= ((uint64_t)data2[2]) << 16;
        case 2: h ^= ((uint64_t)data2[1]) << 8;
        case 1: h ^= ((uint64_t)data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

void* HREgetLocal(hre_key_t key) {
    static_assert(sizeof(pthread_key_t) <= sizeof(hre_key_t));
    return (void*)pthread_getspecific((pthread_key_t)key);
}

void HREsetLocal(hre_key_t key, void* package) {
    static_assert(sizeof(pthread_key_t) <= sizeof(hre_key_t));
    pthread_setspecific((pthread_key_t)key, package);
}

void HREcreateLocal(hre_key_t *key, void (*destructor)(void *)) {
    static_assert(sizeof(pthread_key_t) <= sizeof(hre_key_t));
    *key = 0;
    pthread_key_create((pthread_key_t*)key, destructor);
}

void* RTmalloc(size_t size){
    if(size==0) return NULL;
    void *tmp=malloc(size);
    if (tmp==NULL) Abort("out of memory trying to get %zu",size);
    Debug("allocated %zu from system", size);
    return tmp;
}

void* RTmallocZero(size_t size) {
    if(size==0) return NULL;
    void *tmp=calloc((size + CACHE_LINE_SIZE - 1) >> CACHE_LINE, CACHE_LINE_SIZE);
    return tmp;
}

void* RTalign(size_t align, size_t size) {
    void *ret = NULL;
    errno = posix_memalign(&ret, align, size);
    if (errno) {
    switch (errno) {
        case ENOMEM:
            fprintf(stderr, "out of memory on allocating %zu bytes aligned at %zu",
                  size, align);
        case EINVAL:
            fprintf(stderr, "invalid alignment %zu", align);
        default:
            fprintf(stderr, "unknown error allocating %zu bytes aligned at %zu",
                  size, align);
    }}
    assert (NULL != ret && "Alloc failed");
    Debug("allocated %zu aligned at %zu from system", size, align);
    return ret;
}
void RTfree(void* ptr) {
}

static hre_region_t region = NULL;

hre_region_t
RTgetMallocRegion()
{
    return region;
}

void
RTsetMallocRegion(hre_region_t r)
{
    region = r;
    Debug ("Switched allocator to %p", r);
}

#define MAX_ALIGN_MEMSET (1024*1024)
#define MAX_ALIGN_ZEROS (1024)
static size_t next_calloc = 0;
static void *calloc_table[MAX_ALIGN_ZEROS][3];

void* RTalignZero(size_t align, size_t size) {
    if (region)
        return HREalign(region, align, size);
    if (0 == align) Abort("Zero alignment in RTalignZero");
    if (0 == size) return NULL;
    if (size < MAX_ALIGN_MEMSET) {
        // for small sizes do memset
        void *mem = RTalign(align, size);
        memset (mem, 0 , size);
        Debug("allocated %zu in anonymous pages aligned at %zu from system", size, align);
        return mem;
    }
    // for large sizes use calloc and do manual alignment
    if ((size / align)*align != size) // make size multiple of align
        size = ((size + align) / align)*align;
//    void *p = calloc((size / align + 1), align);
    void *p = mmap (NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0);
    // MAP_PRIVATE && WRITE, because we still want the attached NUMA policy to be followed
    if (p == MAP_FAILED)
    Abort ("mmap failed for size %zu MB", size>>20);
    size_t pp = (size_t)p;
    void *old = p;
    if ((pp / align) * align != pp) // manual alignment only if needed
        p = (void*)((pp / align + 1) * align);
    // store self-aligned allocs in calloc_table
    size_t next = __sync_fetch_and_add (&next_calloc, 1);
    calloc_table[next][0] = p;
    calloc_table[next][1] = old;
    calloc_table[next][2] = (void*)size;
    Debug("allocated %zu in (LARGE) anonymous pages aligned at %zu from system", size, align);
    return p;
}

int
mix (int a, int b, int c)
{
    a = a - b; a = a - c; a = a ^ (((uint32_t) c) >> 13);
    b = b - c; b = b - a; b = b ^ (a << 8);
    c = c - a; c = c - b; c = c ^ (((uint32_t) b) >> 13);
    a = a - b; a = a - c; a = a ^ (((uint32_t) c) >> 12);
    b = b - c; b = b - a; b = b ^ (a << 16);
    c = c - a; c = c - b; c = c ^ (((uint32_t) b) >> 5);
    c = c - a; c = c - b; c = c ^ (((uint32_t) b) >> 15);
    return c;
}

uint64_t mix64 (uint64_t key)
{
    key = (~key) + (key << 21); // key = (key << 21) - key - 1;
    key = key ^ (((int64_t)key) >> 24);
    key = (key + (key << 3)) + (key << 8); // key * 265
    key = key ^ (((int64_t)key) >> 14);
    key = (key + (key << 2)) + (key << 4); // key * 21
    key = key ^ (((int64_t)key) >> 28);
    key = key + (key << 31);
    return key;
}

void HREabort(int code){
    exit(code);
}

void* HREalign(hre_region_t region,size_t align,size_t size){
    return RTalign(align,size);
}

int log_active(log_t log) {
    return 0;
}

void log_message(log_t log,const char*file,int line,int errnum,const char *fmt,...){
}

} // extern "C"

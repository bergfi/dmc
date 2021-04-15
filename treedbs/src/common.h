#include "config.h"
#include <pthread.h>
#include <stdio.h>

#include "murmurhash.h"

typedef void* hre_region_t;
typedef size_t hre_key_t;
typedef void *log_t;

#define EXPECT_FALSE(e) __builtin_expect(e, 0)

#define cas(a, b, c)        __sync_bool_compare_and_swap(a,b,c)
#define cas_ret(a, b, c)    __sync_val_compare_and_swap(a,b,c)
#define fetch_or(a, b)      __sync_fetch_and_or(a,b)
#define fetch_and(a, b)     __sync_fetch_and_and(a,b)
#define fetch_add(a, b)     __sync_fetch_and_add(a,b)
#define add_fetch(a, b)     __sync_add_and_fetch(a,b)
#define or_fetch(a, b)      __sync_or_and_fetch(a,b)
#define fetch_sub(a, b)     __sync_fetch_and_sub(a,b)
#define sub_fetch(a, b)     __sync_sub_and_fetch(a,b)
#define prefetch(a)         __builtin_prefetch(a)

#define mfence() { asm volatile("mfence" ::: "memory"); }

#define max(a,b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a > _b ? _a : _b; \
})

#define min(a,b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a < _b ? _a : _b; \
})

#define swap(a,b) ({ \
    typeof(a) tmp = a; \
    a = b; \
    b = tmp; \
})

#undef HREassert
//#define HREassert(e, ...) do {  if(!(e)) { fprintf(stderr, "ASSERT FAILED[%s:%i]"); fprintf(stderr, "[" #e "]: " __VA_ARGS__); fprintf(stderr, "\n"); abort();} } while(false)
#define HREassert(e,...) \
    if (EXPECT_FALSE(!(e))) {\
        char buf[4096];\
        if (#__VA_ARGS__[0])\
            snprintf(buf, 4096, ": " __VA_ARGS__);\
        else\
            buf[0] = '\0';\
        fprintf(stderr, "[%s:%i] assertion \"%s\" failed%s\n", __FILE__, __LINE__, #e, buf);\
		abort();\
    }

#define Abort(...) {\
    char buf[4096];\
    if (#__VA_ARGS__[0])\
        snprintf(buf, 4096, ": " __VA_ARGS__);\
    else\
        buf[0] = '\0';\
    fprintf(stderr, "Aborting at %s:%u: %s", __FILE__, __LINE__, buf);\
    HREabort(-1);\
}

#define Debug(...) {\
    char buf[4096];\
    if (#__VA_ARGS__[0])\
        snprintf(buf, 4096, ": " __VA_ARGS__);\
    else\
        buf[0] = '\0';\
    fprintf(stdout, "%s:%u: %s", __FILE__, __LINE__, buf);\
}

//uint64_t MurmurHash64 (const void * key, int len, uint64_t seed);
void* HREgetLocal(hre_key_t key);
void HREsetLocal(hre_key_t key, void* package);
void HREcreateLocal(hre_key_t *key, void (*destructor)(void *));
void* RTmalloc(size_t size);
void* RTmallocZero(size_t size);
void* RTalign(size_t align, size_t size);
void RTfree(void* ptr);
void* RTalignZero(size_t align, size_t size);
void HREabort(int code);
void* HREalign(hre_region_t region,size_t align,size_t size);

int log_active(log_t log);
void log_message(log_t log,const char*file,int line,int errnum,const char *fmt,...);

/**
\brief These constructs prevent the compiler from optimizing (reordering) reads
    and writes to memory location. Strong order execution has to be guaranteed
    by the CPU for this to work. It seems like x86 is going to for the
    foreseeable future.
*/
#define atomic_read(v)      (*(volatile typeof(*v) *)(v))
#define atomic_write(v,a)   (*(volatile typeof(*v) *)(v) = (a))

int mix (int a, int b, int c);
uint64_t mix64 (uint64_t key);

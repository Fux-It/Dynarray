#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#define VECTOR_INITIAL_CAPACITY 8

/* put this in some utilities header or something */
#if defined(__GNUC__) || defined(__clang__)

#define FORCE_INLINE __attribute__((always_inline)) inline
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define LIKELY(x) __builtin_expect(!!(x), 1)

#else   /*MSVC is the only crappy compiler that doesnt support this*/

#define UNLIKELY(x) (x)
#define LIKELY(x) (x)

#endif

    

typedef enum
{
    VECTOR_NO_ERROR,
    VECTOR_ALLOCATION_ERROR,
    VECTOR_FREED
} vector_err_flag;

typedef struct
{
    size_t capacity;    /* THIS IS IN BYTES, REMEMBER THIS YOU MONGREL */
    size_t size;        /* NOT IN BYTES, THIS IS THE COUNT BASICALLY */
    size_t elem_size;

    vector_err_flag status;
    void *data;
} vector;

vector initialize_vec(size_t elem_size);

void free_vector(vector *vec);

/* remember to turn it into force_inline */
FORCE_INLINE int vector_push_back(vector *vec, const void *element)
{   
    if(UNLIKELY((vec->size + 1) * vec->elem_size > vec->capacity)) 
    {
        //FUCKING SHIT BRO, this prevents a bug, so we dont end up losing the old ptr when 
        //reallocing, anyways this doubles the capacity
        void *tmp = realloc(vec->data, vec->capacity * 2); 
        if(!tmp)
        {
            vec->status = VECTOR_ALLOCATION_ERROR;
            return -1;
        }
        vec->capacity *= 2;

        vec->data = tmp;
    }
    
    memcpy((char *)vec->data + vec->size * vec->elem_size, element, vec->elem_size);
    vec->size++;

    return 0;
}

FORCE_INLINE size_t round_next_pow2(size_t number)
{
    if(number < 2)
    {
        return 1;
    }
#if defined(__GNUC__) || defined(__CLANG__)

#if SIZE_MAX > 0xFFFFFFFF
    #define builtin_clz(x) __builtin_clzll(x)
#else
    #define builtin_clz(x) __builtin_clz(x)
#endif

    //count the leading bits to figure out the number of bits needed to shift 0x1 to get nearest pow
    return (size_t)0x1 << ((sizeof(size_t) * 8) - (size_t)builtin_clz(--number));
#elif defined(__MSC_VER_)

#if SIZE_MAX > 0xFFFFFFFF
    #define bitscan_reverse(x, y) _BitScanReverse64(x, y)
#else
    #define bitscan_reverse(x, y) _BitScanReverse(x, y)
#endif

    unsigned long idx;
    bitscan_reverse(&idx, --number);

    return (size_t)0x1 << (idx + 1);

#else
    number--;
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
#if SIZE_MAX > 0xFFFFFFFF
    number |= number >> 32;
#endif
    number++;

    return number;
#endif    
}

int resize_vector(vector *vec, size_t size);

int insert_vector(vector *vec, const void *elements, size_t start, size_t end);

static inline int shrink_to_fit_vector(vector *vec)
{
    if(!vec)
        return -1;

    size_t bytesize = vec->size * vec->elem_size;
    if(bytesize < vec->capacity)
    {
        void *tmp = realloc(vec->data, bytesize);
        
        if(!tmp)
        {
            vec->status = VECTOR_ALLOCATION_ERROR;
            return -1;
        }

        vec->data = tmp;
        vec->capacity = bytesize;
    }

    return 0;
}

#define VEC_POP_BACK(vec) vec.size--

#endif


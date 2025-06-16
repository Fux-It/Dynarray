#include "dynarray.h"
#include <stdlib.h>
#include <assert.h>


vector initialize_vec(size_t elem_size)
{
    assert(elem_size != 0 && "VECTOR ERROR, ELEMENT SIZE MUSTN'T BE ZERO");
    vector dynarray = {.elem_size = elem_size, .capacity = VECTOR_INITIAL_CAPACITY * elem_size,
                        .size = 0};

    dynarray.data = malloc(dynarray.capacity);
    
    if(!dynarray.data)
        dynarray.status = VECTOR_ALLOCATION_ERROR;
    else
        dynarray.status = VECTOR_NO_ERROR;



    return dynarray;
}

void free_vector(vector *vec)
{
    free(vec->data);
    vec->status = VECTOR_FREED;

}

/* no overflow protection yet*/
int resize_vector(vector *vec, size_t size)
{
    //only realloc when size > capacity
    if(UNLIKELY(size * vec->elem_size > vec->capacity))
    {
        //the usual doubling
        size_t new_cap_elem = (vec->capacity / vec->elem_size) * 2;
        
        //if this rare case happens, run pow2
        if(new_cap_elem < size)
        {
            new_cap_elem = round_next_pow2(size);
        }
        
        void *tmp = realloc(vec->data, new_cap_elem * vec->elem_size);
        if(!tmp)
        {
            vec->status = VECTOR_ALLOCATION_ERROR;
            return -1;
        }
        vec->capacity = new_cap_elem * vec->elem_size;
        vec->data = tmp;        
        
        memset((char *)vec->data + vec->size * vec->elem_size, 0, 
                (size - vec->size) * vec->elem_size);
    }

    vec->size = size;

    return 0;
}

int insert_vector(vector *vec, const void *elements, size_t start, size_t end)
{
    if(!vec || !elements || end == 0)
        return 0;

    start = start > vec->size ? vec->size : start;

    size_t old_size = vec->size;
    if(resize_vector(vec, vec->size + end))
        return -1;

    //memmove to create space if inserted in the middle
    if(start < old_size)
    {
        memmove((char *) vec->data + (start + end) * vec->elem_size, 
                (char *) vec->data + start * vec->elem_size,
                (old_size - start) * vec->elem_size);
    }

    memcpy((char *) vec->data + start * vec->elem_size, elements, end * vec->elem_size);
    return 0;
}

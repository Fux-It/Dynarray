#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "dynarray.h"
#include <inttypes.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void benchmark_c_vector(size_t count) {
    vector vec = initialize_vec(sizeof(int64_t));
    reserve_vector(&vec, count);

    clock_t start = clock();

    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        int value = i;

        VEC_PUSH_BACK(int, vec, value);
        sum += ((int *) vec.data)[i];
    } 

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("C VECTOR: %.6f seconds\n", elapsed);
    printf("sum - %" PRId64 "\n", sum);

    free_vector(&vec);

}

void benchmark_c_resize(size_t count) {
    vector vec = initialize_vec(sizeof(int64_t));

    clock_t start = clock();

    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {

        resize_vector(&vec, i + 1);
        ((int *) vec.data)[i] = i;
        sum += ((int *) vec.data)[i];
    } 

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("C VECTOR: %.6f secwonds\n", elapsed);
    printf("sum - %" PRId64 "\n", sum);
    printf("capacity - %zu\n", vec.capacity);

    free_vector(&vec);

}

int main(void)
{
    const size_t count = 1000000000;

    printf("BENCHMARKING %zu RESIZES FOR C\n", count);

    benchmark_c_resize(count);

}



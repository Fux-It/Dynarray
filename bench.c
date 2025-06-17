#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "dynarray.h"

void benchmark_c_vector(size_t count) {
    vector vec = initialize_vec(sizeof(int));

    clock_t start = clock();

    for (size_t i = 0; i < count; ++i) {
        int value = i;
        vector_push_back(&vec, &value);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("C VECTOR: %.6f seconds\n", elapsed);

    free_vector(&vec);

}

int main(void)
{
    const size_t count = 10000000;

    printf("BENCHMARKING %zu ELEMENTS FOR C\n", count);

    benchmark_c_vector(count);
}



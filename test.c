#include <stdio.h>
#include "dynarray.h"
/* testing file */


int main(void)
{
    vector test = initialize_vec(sizeof(int));

    for(int i = 0; i < 34; i++)
    {
        VEC_PUSH_BACK(int, test, i);

        printf("CAPACITY GREW TO - %zu & SIZE GREW TO - %zu\n", test.capacity, test.size);
        printf("STATUS - %d\n", test.status);
    }
    
    printf("{");
    for(int i = 0; i < test.size; i++)
    {
        printf(" %d,", ((int *) test.data)[i]);
    }

    printf("\b }\n");

    printf("CAPACITY BEFORE INSERT - %zu, SIZE - %zu\n", test.capacity, test.size);

    int arr[4] = {999, 998, 997, 996};

    insert_vector(&test, arr, 2, 4);
    
    printf("{");
    for(int i = 0; i < test.size; i++)
    {
        printf(" %d,", ((int *) test.data)[i]);
    }
    printf("\b }\n");
    insert_vector(&test, ((int *)test.data) + 7, 2, 4);
    
    printf("{");
    for(int i = 0; i < test.size; i++)
    {
        printf(" %d,", ((int *) test.data)[i]);
    }
    printf("\b }\n");
    printf("CAPACITY AFTER INSERT - %zu, SIZE - %zu\n", test.capacity, test.size);

    shrink_to_fit_vector(&test);
    printf("CAPACITY AFTER SHRINKING - %zu, SIZE - %zu\n", test.capacity, test.size);

    //resize
    resize_vector(&test, 100);
    printf("CAPACITY AFTER RESIZE - %zu, SIZE - %zu\n", test.capacity, test.size);
    
    resize_vector(&test, 1000);
    printf("CAPACITY AFTER RESIZE - %zu, SIZE - %zu\n", test.capacity, test.size);
    
    resize_vector(&test, 10000);
    printf("CAPACITY AFTER RESIZE - %zu, SIZE - %zu\n", test.capacity, test.size);
    
    resize_vector(&test, 100000);
    printf("CAPACITY AFTER RESIZE - %zu, SIZE - %zu\n", test.capacity, test.size);
    free_vector(&test);
}


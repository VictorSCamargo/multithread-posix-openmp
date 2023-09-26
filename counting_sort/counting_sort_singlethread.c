#include <stdlib.h>
#include <stdio.h>

#include "counting_sort.h"

//ToDo should be original
int counting_sort_singlethread(int *array,unsigned int size){

    // Find the largest element of the array
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    int* output = (int *)malloc(size * sizeof(int));

    if (output == NULL) {
        printf("Failed to allocate memory for output.\n");
        return 1;
    }

    // The size of count must be at least (max+1) but
    // we cannot declare it as int count(max+1) in C as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int* count = (int *)calloc(max + 1, sizeof(int));

    if (count == NULL) {
        printf("Failed to allocate memory for count.\n");
        free(output);
        return 1;
    }

    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }

    free(count);
    free(output);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "counting_sort.h"

#define MAX_THREADS 4 // Define num of threads to be used

int max_value;
int *count;
int *input_array;
int *output;

struct ThreadArg {
    int start;
    int end;
};

void *counting_thread(void *arg) {
    struct ThreadArg *targ = (struct ThreadArg*)arg;

    for (int i = targ->start; i < targ->end; i++) {
        int value = input_array[i];
        count[value]++;
    }

    pthread_exit(NULL);
}

void *sorting_thread(void *arg) {
    struct ThreadArg *targ = (struct ThreadArg*)arg;

    for (int i = targ->start; i < targ->end; i++) {
        int value = input_array[i];
        output[count[value] - 1] = value;
        count[value]--;
    }

    pthread_exit(NULL);
}

int counting_sort_posix(int *array, unsigned int size) {
    input_array = array;

    // Find the largest element of the array
    for (int i = 0; i < size; i++) {
        if (input_array[i] > max_value) {
            max_value = input_array[i];
        }
    }

    output = (int *)malloc(size * sizeof(int));
    count = (int *)calloc(max_value + 1, sizeof(int));

    if (output == NULL || count == NULL) {
        printf("Failed to allocate memory.\n");
        free(output);
        free(count);
        return 1;
    }

    pthread_t count_threads[MAX_THREADS];
    pthread_t sort_threads[MAX_THREADS];
    struct ThreadArg args[MAX_THREADS];

    int part_size = size / MAX_THREADS;

    // Init counting threads
    for (int i = 0; i < MAX_THREADS; i++) {
        args[i].start = i * part_size;
        args[i].end = (i == MAX_THREADS - 1) ? size : (i + 1) * part_size;
        pthread_create(&count_threads[i], NULL, counting_thread, &args[i]);
    }

    // Wait for counting threads
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(count_threads[i], NULL);
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max_value; i++) {
        count[i] += count[i - 1];
    }

    // Init sorting threads
    for (int i = 0; i < MAX_THREADS; i++) {
        args[i].start = i * part_size;
        args[i].end = (i == MAX_THREADS - 1) ? size : (i + 1) * part_size;
        pthread_create(&sort_threads[i], NULL, sorting_thread, &args[i]);
    }

    // Wait for sorting threads
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(sort_threads[i], NULL);
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++) {
        input_array[i] = output[i];
    }

    free(output);
    free(count);

    return 0;
}

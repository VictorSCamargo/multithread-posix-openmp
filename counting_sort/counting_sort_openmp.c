#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "counting_sort.h"


int counting_sort_openmp(int *array, unsigned int size){

    omp_set_num_threads(4); // Número de threads

    //Acha o maior número do array
    int max = array[0];
    #pragma omp parallel for
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

    //Tamanho é definido de forma estática
    int* count = (int *)calloc(max + 1, sizeof(int));

    if (count == NULL) {
        printf("Failed to allocate memory for count.\n");
        free(output);
        return 1;
    }

    //Inicia o array de conta com zeros
    #pragma omp parallel for
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    //Guarda o número de ocorrências de cada item
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    //Guarda a soma do valor em si com o imediatamente anterior a ele do array
    #pragma omp parallel for
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    //Acha o index dos elementos do array original no array de conta e guarda no array output
    #pragma omp parallel for
    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    //Copia os elementos ordenados no array original
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }

    free(count);
    free(output);

    return 0;
}

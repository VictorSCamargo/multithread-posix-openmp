#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "bubblesort/bubblesort.h"
#include "quicksort/quicksort.h"
#include "counting_sort/counting_sort.h"

#define MAX_ELEMENT_VALUE 1000

struct FunctionHolder {
    const char *name;
    int (*func)(int *, unsigned int);
};

void free_elements_from_memory(int** elements, int num_arrays) {
  printf("\nFreeing elements from memory...\n");

  for(int i=0;i<num_arrays;i++){
    free(elements[i]);
  }
  free(elements);

  printf("\nFreed elements from memory.");
}

int main(int argc, char **argv) {

    if(argc<3){
        printf("Input %s num_arrays num_elements\n", argv[0]);
        exit(0);
    }

    int num_arrays = atoi(argv[1]);
    int num_elements = atoi(argv[2]);

    printf("\nNum of arrays: %d", num_arrays);
    printf("\nEach array will have %d elements.\n", num_elements);

    struct FunctionHolder sorting_algorithms[] = {
      //{"Bubblesort", bubble}, //ToDo ignoring for tests for now because takes too long
      {"Quicksort", quicksort},
      {"Counting Sort singlethread", counting_sort_singlethread}, //ToDo it is not necessary for the task
      {"Counting sort POSIX", counting_sort_posix},
      {"Counting sort OpenMP", counting_sort_openmp}
    };
    int num_of_algorithms = sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]);

    printf("\nThere are %d sorting algorithms to be tested.", num_of_algorithms);

    int **elements;    
    struct timeval t1[num_of_algorithms];
    struct timeval t2[num_of_algorithms];
    double t_total[num_of_algorithms];

    //ToDo create param to run this to generate new seed if wanted
    //srand(time(NULL));

    // Allocates memory for 'elements'
    elements = (int**)malloc(num_arrays * sizeof(int*));
    if (elements == NULL) {
      printf("Failed to allocate memory for 'elements'.\n");
      fflush(stdout);
      return 1; // Ou qualquer tratamento de erro que você preferir
    }

    for (int i = 0; i < num_arrays; i++) {
      elements[i] = (int*)malloc(num_elements * sizeof(int));
      if (elements[i] == NULL) {
          printf("Failed to allocate memory for 'elements[%d]'.\n", i);
          fflush(stdout);

          for (int j = 0; j < i; j++) {
              free(elements[j]);
          }
          free(elements);

          return 1;
      }
    }

    printf("\nStarting tests.");

    int exit_code = 0;

    for (int i = 0; i < num_of_algorithms; i++) {
      const char* func_name = sorting_algorithms[i].name;

      printf("\nTesting %s... ", func_name);
      fflush(stdout);

      gettimeofday(&t1[i], NULL);

      exit_code = 0;

      for (int j = 0; j < num_arrays; j++) {
        exit_code = sorting_algorithms[i].func(elements[j], num_elements);

        if (exit_code != 0) {
          printf("Sorting algorithm %s failed. Ending program.", sorting_algorithms[i].name);

          free_elements_from_memory(elements, num_arrays);

          return 1;
        }
      }

      gettimeofday(&t2[i], NULL);

      printf("%s finalized.", func_name);
      fflush(stdout);
    }
    printf("\nTests finished.");

    free_elements_from_memory(elements, num_arrays);

    printf("\nCalculating times...");
    for (int i = 0; i < num_of_algorithms; i++) {
      t_total[i] = (t2[i].tv_sec - t1[i].tv_sec) + ((t2[i].tv_usec - t1[i].tv_usec)/1000000.0);
    }

    printf("\n\nTotal times:");
    for (int i = 0; i < num_of_algorithms; i++) {
      printf("\n%s: %f", sorting_algorithms[i].name, t_total[i]);
    }

    printf("\n"); // new line for terminal

    return 0;
}
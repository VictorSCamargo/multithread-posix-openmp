#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "bubblesort/bubblesort.h"
#include "quicksort/quicksort.h"
#include "counting_sort/counting_sort.h"


struct FunctionHolder {
    const char *name;
    int (*func)(int *, unsigned int);
};

int main(int argc, char **argv) {

    if(argc<3){
        printf("Digite %s Num_arrays Num_elementos\num_arrays", argv[0]);
        exit(0);
    }

    int num_arrays = atoi(argv[1]);
    int num_elementos = atoi(argv[2]);	

    struct FunctionHolder sorting_algorithms[] = {
      {"Bubblesort", bubble},
      {"Quicksort", quicksort},
      {"Counting Sort singlethread", counting_sort_singlethread},
      {"Counting sort POSIX", counting_sort_posix},
      {"Counting sort OpenMP", counting_sort_openmp}
    };
    int num_of_algorithms = sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]);

    printf("\nThere are %d sorting algorithms to be tested.", num_of_algorithms);

    int **elementos;    
    struct timeval t1[num_of_algorithms];
    struct timeval t2[num_of_algorithms];
    double t_total[num_of_algorithms];

    //ToDo create param to run this to generate new seed if wanted
    //srand(time(NULL));

    printf("\nGenerating test array...");
    // Allocates memory
    elementos=(int**)malloc(num_arrays*sizeof(int*));
    for (int i = 0; i < num_arrays; i++) {
      elementos[i]=(int*)malloc(num_elementos*sizeof(int));
    }

    // Asigns random values to arrays
    for (int i = 0; i < num_arrays; i++) {
      for (int j = 0; j < num_elementos; j++) {
        elementos[i][j] = rand() % 1000;
      }
    }
    printf("\nArrays of elements created.");

    printf("\nStarting tests.");
    for (int i = 0; i < num_of_algorithms; i++) {
      const char* func_name = sorting_algorithms[i].name;

      printf("\nTesting %s... ", func_name);

      gettimeofday(&t1[i], NULL);

      for (int j = 0; j < num_arrays; j++) {
        sorting_algorithms[i].func(elementos[i], num_elementos);
      }

      gettimeofday(&t2[i], NULL);

      printf("%s finalized.", func_name);
    }
    printf("\nTests finished.");

    printf("\nFreeing elements from memory...");
    for(int i=0;i<num_arrays;i++){
      free(elementos[i]);
    }
    free(elementos);

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
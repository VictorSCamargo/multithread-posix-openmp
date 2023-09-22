#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "bubblesort/bubblesort.h"
#include "quicksort/quicksort.h"
#include "counting_sort/counting_sort.h"

int main(int argc, char **argv) {
    int **elementos,num_arrays,num_elementos,i,j;    
    struct timeval t1, t2;
    double t_total;

    if(argc<3){
        printf("Digite %s Num_arrays Num_elementos\num_arrays", argv[0]);
        exit(0);
    }
    num_arrays = atoi(argv[1]);
    num_elementos = atoi(argv[2]);	

    //ToDo create param to run this to generate new seed if wanted
    //srand(time(NULL));

    /*Aloca memória para os vetores*/
    elementos=(int**)malloc(num_arrays*sizeof(int*));
    for(i = 0; i < num_arrays; i++)
        elementos[i]=(int*)malloc(num_elementos*sizeof(int));

    /*Popula os arrays com elementos aleatorios entre 0 e 1000*/
    for(i = 0; i < num_arrays; i++) 
        for (j = 0; j < num_elementos; j++)
        elementos[i][j] = rand() % 1000;

    gettimeofday(&t1, NULL);
    for (i = 0; i < num_arrays; i++)
        bubble(elementos[i],num_elementos);
    gettimeofday(&t2, NULL);
    
    t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec)/1000000.0);

    /*Libera memoria alocada*/
    for(i=0;i<num_arrays;i++){
      free(elementos[i]);
    }
    free(elementos);

    printf("tempo total = %f\num_arrays", t_total);

    return 0;
}
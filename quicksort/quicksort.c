#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include "quicksort.h"

// function that should change the position between the two elements
void troca(int *array, int i, int j)
{
	int aux = array[i];
	array[i] = array[j];
	array[j] = aux;
}

// partition and return the index of pivô
int particiona(int *array, int inicio, int fim)
{
	int pivo, pivo_indice, i;
	
	pivo = array[fim]; 
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		if(array[i] <= pivo)
		{
			troca(array, i, pivo_indice);
			pivo_indice++;
		}
	}
	
	troca(array, pivo_indice, fim);
	
	return pivo_indice;
}

// choose a aleatory pivo for avoid the worst case of quicksort
int particiona_random(int *array, int inicio, int fim)
{
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	troca(array, pivo_indice, fim);

	return particiona(array, inicio, fim);
}

// execute the quick_sort algorithm
void quick_sort(int *array, int inicio, int fim)
{
	if(inicio < fim)
	{
		int pivo_indice = particiona_random(array, inicio, fim);
		
		quick_sort(array, inicio, pivo_indice - 1);
		quick_sort(array, pivo_indice + 1, fim);
	}
}

int quick(int *array,unsigned int size)
{
    quick_sort(array, 0, size - 1);
	int i;
	for(i = 0; i < size; i++)
 		printf("%d ", array[i]);

	return 0;
}

#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include "quicksort.h"

// função que realiza a troca entre dois elementos
void troca(int *array, int i, int j)
{
	int aux = array[i];
	array[i] = array[j];
	array[j] = aux;
}

// particiona e retorna o índice do pivô
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

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(int *array, int inicio, int fim)
{
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	troca(array, pivo_indice, fim);

	return particiona(array, inicio, fim);
}

// Executa o algoritmo quick sort
void quick_sort(int *array, int inicio, int fim)
{
	if(inicio < fim)
	{
		int pivo_indice = particiona_random(array, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(array, inicio, pivo_indice - 1);
		quick_sort(array, pivo_indice + 1, fim);
	}
}

int quick(int *array,unsigned int size)
{
    quick_sort(array, 0, size - 1);

	return 0;
}

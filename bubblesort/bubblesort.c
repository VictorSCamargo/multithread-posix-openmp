#include <stdlib.h>

#include "bubblesort.h"

int bubble(int *array,unsigned int size){
  int i,j;
  int temp;
  for(i = 0; i < size-1; i++){       
    for(j = 0; j < size-i-1; j++){          
      if(array[j] > array[j+1]){               
        temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
  return 0;
}

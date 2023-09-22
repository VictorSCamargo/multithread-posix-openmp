#ifndef __COUNTING_SORT_H__ // C header file boiler plate
#define __COUNTING_SORT_H__

int counting_sort_openmp(int *array,unsigned int size);

int counting_sort_posix(int *array,unsigned int size);

int counting_sort_singlethread(int *array,unsigned int size);

#endif /* __COUNTING_SORT_H__ */

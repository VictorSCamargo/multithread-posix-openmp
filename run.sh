#!/bin/bash

# Compiles files
eval "gcc main.c bubblesort.c quicksort.c counting_sort_openmp.c counting_sort_posix.c -o app.out"

# Runs output
eval "./app.out"

#!/bin/bash

output_name="app.out"

compile_command="gcc \
main.c \
bubblesort/bubblesort.c \
quicksort/quicksort.c \
counting_sort/counting_sort_openmp.c \
counting_sort/counting_sort_posix.c \
-o $output_name"

# Compiles files
eval $compile_command

# Runs output
eval "./$output_name"

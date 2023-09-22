#!/bin/bash

output_name="app.out"

compile_command="gcc \
main.c \
bubblesort/bubblesort.c \
quicksort/quicksort.c \
counting_sort/counting_sort_openmp.c \
counting_sort/counting_sort_posix.c \
counting_sort/counting_sort_singlethread.c \
-o $output_name"

# Compiles files
eval "$compile_command"
compilation_exit_code=$?

if [[ $compilation_exit_code != 0 ]]; then
    echo "Compilation failed. Script ended."
    exit 1
fi

# Default values
param_1="1000"
param_2="1000"

# Verify if 2 parameters were received
if [ $# -eq 2 ]; then
    param_1="$1"
    param_2="$2"
else
    echo -e "Running with default parameters: $param_1 $param_2\n"
fi

# Runs output
eval "./$output_name $param_1 $param_2"

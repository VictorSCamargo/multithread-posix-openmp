#!/bin/bash

output_name="app.out"

compile_command="gcc \
main.c \
bubblesort/bubblesort.c \
quicksort/quicksort.c \
counting_sort/counting_sort_openmp.c \
counting_sort/counting_sort_posix.c \
counting_sort/counting_sort_singlethread.c \
-o $output_name -pthread"

# Compiles files
eval "$compile_command"
compilation_exit_code=$?

if [[ $compilation_exit_code != 0 ]]; then
    echo "Compilation failed. Script ended."
    exit 1
fi

# Default values
num_arrays="500"
num_elements="100000"

# Verify if 2 parameters were received
if [ $# -eq 2 ]; then
    num_arrays="$1"
    num_elements="$2"
else
    echo -e "Running with default parameters: $num_arrays $num_elements\n"
fi

# Runs output
eval "./$output_name $num_arrays $num_elements"

exit_code="$?"

echo -e "\nExit code: $exit_code"

exit $exit_code # Returns last command output code

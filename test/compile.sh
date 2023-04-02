#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./compile.sh <buffersize>"
    exit 1
fi
# Compile the program
cc -g -Wall -Wextra -Werror -D BUFFER_SIZE=$1 test.c ../get_next_line.c ../get_next_line_utils.c
# Run the program
#./a.out
# Debug the program
valgrind --leak-check=yes --track-origins=yes ./a.out 2> valgrind_result.txt
# Display the result
cat valgrind_result.txt
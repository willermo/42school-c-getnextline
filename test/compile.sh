#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./compile.sh <buffersize> [[debug <filename> | interactive ] | [debug <filename> | interactive ] ]"
    exit 1
fi
# Compile the program
cc  -g -Wall -Wextra -Werror -D BUFFER_SIZE=$1 \
    test.c test_utils.c ../get_next_line.c ../get_next_line_utils.c
# Run the program
if [ "$2" = "debug" ]
then
    # Debug the program
    valgrind --leak-check=yes --track-origins=yes ./a.out ${3} 2>&1
    # Display the result
    # cat valgrind_result.txt
    exit 0
elif [ "$2" = "run" ]
then
    # Run the program
    ./a.out ${3}
    exit 0
fi
exit 0
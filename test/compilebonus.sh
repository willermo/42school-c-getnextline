#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./compilebonus.sh <buffersize> [[run static | interactive ] | [debug static | interactive ] ]"
    exit 1
fi
# Compile the program
cc  -g -Wall -Wextra -Werror -D BUFFER_SIZE=$1 \
    test_bonus.c test_utils_bonus.c ../get_next_line_bonus.c ../get_next_line_utils_bonus.c
# Run the program
if [ "$2" = "debug" ]
then
    # Debug the program
    valgrind --leak-check=yes --track-origins=yes --show-leak-kinds=all -s ./a.out ${3} 2>&1
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
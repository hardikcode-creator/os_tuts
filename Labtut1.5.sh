#!/bin/bash
# This script prints all the command-line arguments passed to it

echo "Command-line arguments passed:"

for arg in "$@"; do
    echo $arg
done

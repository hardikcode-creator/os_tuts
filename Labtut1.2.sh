#!/bin/bash
# This script takes two integers as input from the command line and computes their sum.

num1=$1
num2=$2

sum=$((num1 + num2))

echo "The sum of $num1 and $num2 is: $sum"

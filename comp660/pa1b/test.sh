#!/bin/bash
show=1
echo "running pa1a"
rm ./pa1
gcc pa1a.c -o pa1 -lm -std=c99  -fopenmp 
./pa1 10 100 $show 0 

echo "running pa1b"
rm ./pa1
gcc pa1b.c -o pa1 -lm -std=c99  -fopenmp 
./pa1 10 100 $show 1 4

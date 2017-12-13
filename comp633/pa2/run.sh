#!/bin/bash
thread=(1 2 4 8 16 32 64 128 256)
echo "running pa2"
rm ./pa2
gcc pa2.c -o pa2 -lm -std=c99  -O3
./pa2 input1.txt


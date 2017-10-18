#!/bin/bash
gcc play.c -o play -lm -std=c99  -fopenmp 
./play

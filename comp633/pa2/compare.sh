#!/bin/bash


thread=(1 2 4 8 16 32 64 128 256)
echo "running pa2"
rm ./pa2
gcc pa2.c -o pa1 -lm -std=c99  -fopenmp -O3


for i in "${array[@]}"
do
    for j in "${thread[@]}"
    do
        echo $i, $j
	    ./pa1 $i $run $show 2 $j
    done
done


echo "running pa1a"
rm ./pa1
gcc pa1a.c -o pa1 -lm -std=c99  -fopenmp  -O3
for i in "${array[@]}"
do
	./pa1 $i $run $show 2
done

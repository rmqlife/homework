#!/bin/bash
show=0
array=(200 500 1000 2000 5000 10000 20000)
run=20
thread=(1 2 4 8 16 32 64 128 256)
echo "running pa1b"
rm ./pa1
gcc pa1b-hp.c -o pa1 -lm -std=c99  -fopenmp -O3


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
gcc pa1a-hp.c -o pa1 -lm -std=c99 -fopenmp -O3
for i in "${array[@]}"
do
	./pa1 $i $run $show 2
done

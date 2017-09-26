
array=("-O0" "-O1" "-O2" "-O3" "-Os")

echo "method1"
for i in "${array[@]}"
do
	echo $i
	gcc pa1_1.c -o pa1 -lm -std=c99 $i -fopenmp
	./pa1 1000 4
done

echo "method2"
for i in "${array[@]}"
do
	echo $i
	gcc pa1_2.c -o pa1 -lm -std=c99 $i -fopenmp
	./pa1 1000 4
done





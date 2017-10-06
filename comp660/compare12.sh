array=(10 20 50 100 200 500 )

echo "method 1"
gcc pa1_1.c -o pa1 -lm -std=c99 -fopenmp 
for i in "${array[@]}"
do
	./pa1 $i 4
done

echo "method 2"
gcc pa1.c -o pa1 -lm -std=c99  -fopenmp 
for i in "${array[@]}"
do
	./pa1 $i 4
done

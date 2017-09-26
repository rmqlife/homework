array=(10 20 50 100 200 500 1000 2000 5000 10000)

echo "method 1"
gcc pa1_1.c -o pa1 -lm 
for i in "${array[@]}"
do
	./pa1 $i
done

echo "method 2"
gcc pa1.c -o pa1 -lm 
for i in "${array[@]}"
do
	./pa1 $i
done
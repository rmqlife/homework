
array=(10 100 1000)

echo "none"
gcc pa1.c -o pa1 -lm
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O0"
gcc pa1.c -o pa1 -lm -O0
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O1"
gcc pa1.c -o pa1 -lm -O1
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O2"
gcc pa1.c -o pa1 -lm -O2
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O3"
gcc pa1.c -o pa1 -lm -O3
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-Os"
gcc pa1.c -o pa1 -lm -Os
for i in "${array[@]}"
do
	./pa1 $i
done




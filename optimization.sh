
array=(10 100 1000)

echo "none"
gcc pa1.c -o pa1 -lm -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O0"
gcc pa1.c -o pa1 -lm -O0 -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O1"
gcc pa1.c -o pa1 -lm -O1 -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O2"
gcc pa1.c -o pa1 -lm -O2 -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-O3"
gcc pa1.c -o pa1 -lm -O3 -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done

echo "-Os"
gcc pa1.c -o pa1 -lm -Os -std=c99
for i in "${array[@]}"
do
	./pa1 $i
done




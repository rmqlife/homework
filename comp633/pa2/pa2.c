#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#define MAX_LENGTH 100
int main(int argc, char *argv[]){
    FILE *fin;
    if ( argc<=1 || (fin = fopen(argv[1],"r")) == NULL ){
        printf("Error open input file\n");
        return 1;
    }
    int data[MAX_LENGTH];
    int input_size;
    fscanf(fin, "%d,", &input_size);
    for (int i = 0; i < input_size; i++){
        fscanf(fin, "%d,", &data[i] );
    }

    // quick sort


    for (int i = 0; i < input_size; i++){
        printf("%d ", data[i]);
    }

    return 0;
}

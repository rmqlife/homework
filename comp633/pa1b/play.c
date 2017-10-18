#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <omp.h>
#include "util.h"

int main(){
int count[20];
for (int i=0; i<20; i++)
    count[i]=0;
#pragma omp parallel for
for (int j=0; j<2; j++)
    for (int i=0; i<20; i++){
        count[i]++;
        }

for (int i=0; i<20; i++){
    printf("%i\n", count[i]);
}
return 0;
}


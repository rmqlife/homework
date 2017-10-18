#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <omp.h>
#include "util.h"






int main(int argc, char *argv[]){
	if(argc<=4) {
        printf("Please input type, 0 for generate bodies, 1 for load bodies");
        exit(1);
    }
    

    int body_num = atoi(argv[1]);
    int K_times = atoi(argv[2]);
    int show_fag = atoi(argv[3]);
    int type = atoi(argv[4]);
    body b[body_num];
    
    //default case generate bodies and save
    if (type==0)
        for (int j=0;j<body_num;j++){
	        b[j] = set_body(rand2(),rand2(),rand2(),rand2(),rand2());
	    FILE *fout;
        if ( (fout = fopen("body.out","wb")) == NULL ){
            printf("Error open output file\n");
            return 1;
        }
        fwrite(&b, sizeof(body)*body_num, 1, fout);
        fclose(fout);
    }
    
    //load bodies 
    if (type = 1) {
        FILE *fin;
        if ( (fin = fopen("body.out","rb")) == NULL ){
            printf("Error open input file\n");
            return 1;
        }
        fread(&b, sizeof(body)*body_num, 1, fin);
    }
    
    //generate without save
    if (type==2)
        for (int j=0;j<body_num;j++){
	        b[j] = set_body(rand2(),rand2(),rand2(),rand2(),rand2());
    }

    
	double DeltaT = 1e-03;
	double G = 1;
	if (show_fag){
		for (int j=0;j<body_num;j++){
			printf("b %i: ",j);
			printf(" vel: "); print_vec2(b[j].vel);
			printf(" pos: "); print_vec2(b[j].pos);
			printf(" mass: %f", b[j].m);
			printf("\n");
		}
	}
	vec2 momentum = set_vec2(0,0);
	// check momentum
	if (show_fag){
		for (int j=0;j<body_num;j++){
			momentum = add_vec2(momentum, times_vec2(b[j].m , b[j].vel));
		}sizeof
		printf("Initial momentum: "); print_vec2(momentum);
		printf("\n");
	}
	// count seconds
    double begin, end;
	#pragma omp master
	{
        begin = omp_get_wtime();  
            for (int i=0;i<K_times;i++){
		
		        /* clear accs */
		        for (int j=0;j<body_num;j++)
			        b[j].acc = set_vec2(0,0);
			     	    
	            /* compute acc */
	            for (int j=0;j<body_num;j++){
		            for (int k=0;k<body_num;k++){
			            // not sure the order!!!!
			            vec2 r = add_vec2(b[k].pos, minus_vec2(b[j].pos));
			            //print_vec2(r);
			            double r_length = length_vec2(r);
			            if (r_length<0.000001)
				            continue;
			            double temp = G*b[j].m*b[k].m/r_length/r_length/r_length;				
			            b[j].acc = add_vec2(b[j].acc, times_vec2(temp/b[j].m, r));
			            // newton's third law
			            //b[k].acc = add_vec2(b[k].acc, times_vec2(temp/b[k].m, minus_vec2(r)));
		            }		
                }
                
                /* update vel,pos*/
	            for (int j=0;j<body_num;j++){
		            //printf("acc:"); print_vec2(b[j].acc); printf("\n");
		            b[j].vel = add_vec2(b[j].vel, times_vec2(DeltaT, b[j].acc));
		            b[j].pos = add_vec2(b[j].pos, times_vec2(DeltaT, b[j].vel));
	            }
	        }
	        // count seconds
        end = omp_get_wtime();  
    }
	double time_spent = (double)(end - begin);
	double performance =(double) body_num*body_num*K_times/1e06/time_spent;
	printf("%i %f %f\n", body_num, time_spent, performance);

	momentum = set_vec2(0,0);

	if (show_fag){
		/*print each velocities*/
		for (int j=0;j<body_num;j++){
			printf("b %i: ",j);
			printf(" pos: "); print_vec2(b[j].pos);
			printf(" vel: "); print_vec2(b[j].vel);
			printf("\n");
		}
		// check momentum
		for (int j=0;j<body_num;j++)
			momentum = add_vec2(momentum, times_vec2(b[j].m , b[j].vel));
		printf("Final momentum: "); print_vec2(momentum);
		printf("\n");
	}
    return 0;
}

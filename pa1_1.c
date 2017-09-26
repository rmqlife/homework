#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <omp.h>

typedef struct{
	double x;
	double y;
} vec2;

vec2 set_vec2(double x1,double x2){
	vec2 v;
	v.x = x1;
	v.y = x2;
	return v;
}

vec2 add_vec2(vec2 v1,vec2 v2){
	return set_vec2(v1.x+v2.x,v1.y+v2.y);
}

vec2 minus_vec2(vec2 v){
	return set_vec2(-v.x,-v.y);
}

vec2 times_vec2(double a, vec2 v){
	return set_vec2(v.x*a, v.y*a);
}

int print_vec2(vec2 v){
	printf("(%f, %f)",v.x,v.y);
	return 0;
}

double length_vec2(vec2 v){
	return  sqrt(v.x*v.x + v.y*v.y);
}

double dist_vec2(vec2 a,vec2 b){
	return length_vec2(add_vec2(a,minus_vec2(b)));
}

typedef struct{
	vec2 vel,pos,acc;
	double m;
} body;


body set_body(double x0,double x1,double x2,double x3,double x4){
	body b;
	b.m = x0;
	b.pos = set_vec2(x1,x2);
	b.vel = set_vec2(x3,x4);
	b.acc = set_vec2(0,0);
	return b;
}
/*
nbref sequential all-pairs n-body, n = 3, nts = 6325914, G = 1, DeltaT = 
	Time = 0
	P0 = (-0.97000436,0.24308753)   V0 = (-0.46620368,-0.43236573)  m = 1
	P1 = (0.97000436,-0.24308753)   V1 = ()  m = 1
	P2 = (0,0)   V2 = (0.93240737,0.86473146)  m = 1


	Time = 3.162957
	P0 = (0.97000754,0.24311667)   V0 = (0.46624203,-0.43234625)  m = 1
	P1 = (-0.97003188,-0.24309202)   V1 = (0.46616351,-0.43236621)  m = 1
	P2 = (2.4340532e-05,-2.4652558e-05)   V2 = (-0.93240554,0.86471246)  m = 1

	Time = 6.325914
	P0 = (-0.96997182,0.24313017)   V0 = (-0.46636412,-0.43232847)  m = 1
	P1 = (0.9701019,-0.24301235)   V1 = (-0.46601452,-0.432412)  m = 1
	P2 = (-0.00013007996,-0.00011781508)   V2 = (0.93237864,0.86474047)  m = 1

	Initial momentum = (0,       0)
	Final   momentum = (-1.726397e-13, -6.71685e-14)
	Relative error = 1.85246e-13
*/


double rand2()
{
    return (double)rand() / (double)RAND_MAX ;
}

int main(int argc, char *argv[]){
	if(argc<=2) {
        printf("You did not feed me arguments, I will die now :( ...");
        exit(1);
     } 

	int body_num = atoi(argv[1]);;
	int K_times = atoi(argv[2]);
	body b[body_num];
	int show_fag = 0;
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
		}
		printf("Initial momentum: "); print_vec2(momentum);
		printf("\n");
	}
	// count seconds
	clock_t begin = clock();
	double begin = omp_get_wtime();

	
    for (int i=0;i<K_times;i++){
		
		/* clear accs */
		for (int j=0;j<body_num;j++)
			b[j].acc = set_vec2(0,0);
			
		/* compute acc */
		for (int j=0;j<body_num;j++)
			for (int k=0;k<body_num;k++){
				if (j==k)
					continue;
				// not sure the order!!!!
				vec2 r = add_vec2(b[k].pos, minus_vec2(b[j].pos));
				//print_vec2(r);
				double r_length = length_vec2(r);
				if (r_length<0.000001)
					continue;
				double temp = G*b[j].m*b[k].m/r_length/r_length/r_length;				
				b[j].acc = add_vec2(b[j].acc, times_vec2(temp/b[j].m, r));
			}		
		
		/* update vel,pos*/
		for (int j=0;j<body_num;j++){
			//printf("acc:"); print_vec2(b[j].acc); printf("\n");
			b[j].vel = add_vec2(b[j].vel, times_vec2(DeltaT, b[j].acc));
			b[j].pos = add_vec2(b[j].pos, times_vec2(DeltaT, b[j].vel));
		}
		
		if (show_fag){
			printf("time %f \n",(double) i*DeltaT); 
			/*print each velocities*/
			for (int j=0;j<body_num;j++){
				printf("b %i: ",j);
				printf(" pos: "); print_vec2(b[j].pos);
				printf(" vel: "); print_vec2(b[j].vel);
				printf("\n");
			}
		}
		
	    //printf("time spent %f\n", time_spent);
	}
	// count seconds
	double end =  omp_get_wtime();
	double time_spent = (double)(end - begin);
	double performance =(double) body_num*body_num*K_times/1e06/time_spent;
	printf("%i %lf %lf\n", body_num, time_spent, performance);

	momentum = set_vec2(0,0);

	if (show_fag){
		// check momentum
		for (int j=0;j<body_num;j++)
			momentum = add_vec2(momentum, times_vec2(b[j].m , b[j].vel));
		printf("Final momentum: "); print_vec2(momentum);
		printf("\n");
	}
    return 0;
}

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

double rand2(){
    return (double)rand() / (double)RAND_MAX ;
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


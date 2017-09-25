#include <stdio.h>
#include <time.h>
#include <math.h>

struct vec2{
	double x,y;
}

int set_vec2(vec2,double x1,double x2){
	vec2.x = x1;
	vec2.y = x2;
	return 0;
}

struct body{
	vec2 vel,pos;
	double m;
}

int set_body(body b, double x0,double x1,double x2,double x3,double x4){
	b.m = x0
	set_vec2(b.pos,x1,x2);
	set_vec2(b.vel,x3,x4);
	return 0;
}

double dist2(vec2 a,vec2 b){
	return  sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))
}




nbref sequential all-pairs n-body, n = 3, nts = 6325914, G = 1, DeltaT = 
	Time = 0
	P0 = (-0.97000436,0.24308753)   V0 = (-0.46620368,-0.43236573)  m = 1
	P1 = (0.97000436,-0.24308753)   V1 = ()  m = 1
	P2 = (0,0)   V2 = (0.93240737,0.86473146)  m = 1

int main(){
	body b[3];
	set_body(b[0],1,-0.97000436,0.24308753,-0.46620368,-0.43236573);
	set_body(b[1],1,0.97000436,-0.24308753,-0.46620368,-0.43236573);
	set_body(b[2],1,0,0,0.93240737,0.86473146);
	double DeltaT = 1e-06;
	double G = 1;

    for (int i=1;i<100;i++){
		clock_t begin = clock();

	/* here, do your time-consuming job */

		clock_t end = clock();
		double time_spent = (double)(end - begin);

	    printf("time spent %f\n", time_spent);

	    //update pos
	    


	}
    return 0;
}

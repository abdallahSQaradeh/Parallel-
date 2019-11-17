#include<iostream>
#include <random>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
using namespace std;
double rand_float_double(double a, double b) {
	return ((double)rand() / RAND_MAX) * (b - a) + a;
}
int main(int argc, char ** argv )
{
int seed;
int niter = 1000000;            
    double x,y;                    
    int i;                          
        long long int count=0;               
    double z;                      
    double pi;                     
        int numthreads = 16;
 
    #pragma omp parallel firstprivate(x, y, z, i) shared(count) num_threads(numthreads)
    {
        srandom((int)time(NULL) ^ omp_get_thread_num());    //Give random() a seed value
        #pragma for rduction(+:count)
        for (i=0; i<niter; ++i)             
        {
            x = rand_float_double(-1.0,1.0);      //gets a random x coordinate
            y = rand_float_double(-1.0,1.0);     //gets a random y coordinate
            z = sqrt((x*x)+(y*y));  
    //    cout<<x<< " "<<y<<" "<<z<<endl;        //Checks to see if number is inside unit circle
        if (z<=1)
        {
                ++count;           
        }
    }
    }
    cout<<i<<endl;
        pi = ((double)count/(double)(niter*numthreads))*4.0;
        printf("Pi: %f\n", pi);
return 0;

}
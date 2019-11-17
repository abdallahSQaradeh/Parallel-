#include"func.h"
#include<iostream>
#include <cstdlib>
#include<math.h>

float func(float x);
using namespace std;
float Trap(float a , float b, int trap_count,float base_len )
{
    float estimate ,x;
    int i;
    estimate = (func(a) + func(b))/2.0;
    for(i=0;i<trap_count;i++)
    {
        x = a + i*base_len;
        estimate +=func(x);
    }
    estimate = estimate *base_len;
      return estimate;
}
int main(int  argv , char ** argc)
{
    
    float a,b,n,h;
    if(argv>2){
    a= atoi(argc[1]);
    b=atoi(argc[2]);
    n=atoi(argc[3]);
    }
    else{

        cout<<"you didn't enter the appropirate number of parameter "<<endl;
        exit(1);
    }
        h=(b-a)/n;
    cout<<" approximation of trapezoid = "<<Trap(a,b,n,h)<<endl;

    return 0;
}
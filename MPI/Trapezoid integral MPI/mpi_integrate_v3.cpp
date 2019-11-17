#include"func.h"
#include<iostream>
#include<mpi.h>
#include <cstdlib>
float func(float x);
using namespace std;
float Trap(float left_end_point , float right_end_point, int trap_count,float base_len )
{
    float estimate ,x;
    int i;
    estimate = (func(left_end_point) + func(right_end_point))/2.0;
    for(i=0;i<=trap_count-1;i++)
    {
        x = left_end_point + i*base_len;
        estimate +=func(x);
    }
    estimate = estimate *base_len;
    return estimate;
}
int main(int  argv , char ** argc)
{
    float b,a;
    float local_start , local_end,local_n, n ,h,source;
    int size , rank;
    float local_integral,total_integral;
    if(argv>2){
    a= atoi(argc[1]);
    b=atoi(argc[2]);
    n=atoi(argc[3]);
    }
    else{

        cout<<"you didn't enter the appropirate number of parameter "<<endl;
        exit(1);
    }
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    h=(b-a)/n;
    local_n = n/size;
    local_start = a+ rank *local_n*h;
    local_end = local_start + local_n *h;
    local_integral = Trap(local_start,local_end,local_n,h);
    MPI_Reduce(&local_integral,& total_integral  ,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        cout<<" when n = " <<n<<" trapezoid from "<<a ;
        cout<<" to "<<b<<" = " <<total_integral<<endl;
    }
    
   MPI_Finalize();
   return 0; 
}
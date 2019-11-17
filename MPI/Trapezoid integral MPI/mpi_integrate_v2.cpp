#include"func.h"
#include<iostream>
#include <cstdlib>
#include<mpi.h>
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
 

    float b,a,n;
    float local_start , local_end,local_n,h;
    int source;
    int size , rank;
    float local_integral,total_integral=0;
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

    if(rank!=0)
    {
        MPI_Send(&local_integral , 1 , MPI_FLOAT,0,0,MPI_COMM_WORLD);
    }
            total_integral = local_integral;
            for(source=1;source<size;source++){
            MPI_Recv(&local_integral,1,MPI_FLOAT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_integral = total_integral+local_integral;    
            }   
        
    if(rank==0)
    {
        cout<<" when n = " <<n<<" trapezoid from "<<a ;
        cout<<" to "<<b<<" = " <<total_integral<<endl;
    }
    
   MPI_Finalize();
   return 0; 
}
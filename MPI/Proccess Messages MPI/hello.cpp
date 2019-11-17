#include<iostream>
#include<string.h>
#include<mpi.h>
using namespace std;
int main()
	{
		int myrank , comm_size;
		MPI_Init(NULL,NULL);
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
		MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
		if(myrank==0)
			cout<<"hello from "<< myrank<<endl;
		else if(myrank==1 || myrank==3)
			cout<<"hi from "<< myrank<<endl;
		else
			cout<<"hello world from "<<myrank <<endl;
	
		
		MPI_Finalize();
return 0;
	}

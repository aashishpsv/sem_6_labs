#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	 
	 int rank,size;
	 int arr[9]={18,523,301,1234,2,14,108,150,1928};
	 int arr2[9];

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);

	int no=arr[rank];
  	int rev=0;
	int temp=0;
	while(no>0)
	{
		temp=no%10;
		rev=rev*10+temp;
		no=no/10;
	}
	arr[rank] =rev;
	arr2[rank]=rev;
    MPI_Finalize();

	for(int i=0;i<9;i++){if(arr2[i]!=0){ printf("(%d)%d, \n",rank,arr2[i]);}}
	 return 0;

}
#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	 
	 int rank,size,pow=5;

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);
	 if(rank==0){pow=1;}
	 else{
	 for(int i=0;i<rank;i++){
	    pow= pow*5;
	 }
	 }
	 printf("pow(5,%d) is:%d \n",rank,pow);
	 MPI_Finalize();
	 return 0;

}
#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	 
	 int rank,size;
	 int a=12,b=6;
	 int var;

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);
	 if(rank==0){
	 	var = 12+6;
	    printf("operation is addition,+. so 12+6=%d \n",var);
	   }
	 else if(rank==1){
	 	var =12-6;
	    printf("operation is subraction,-. so 12-6=%d \n",var);
	   }
	  else if(rank==2){
	 	var =12*6;
	    printf("operation is multiplication,*. so 12*6=%d \n",var);
	   }
	  else if(rank==3){
	 	var = 12/6;
	    printf("operation is division,/.  so 12/6=%d \n",var);
	   }



	 MPI_Finalize();
	 return 0;

}
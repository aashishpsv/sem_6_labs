#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	//x=10;
	if(rank==0){
		//x=10;
		printf("entrt");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"sent %d from process 0\n",x);
		fflush(stdout);
		//MPI_Barrier(MPI_COMM_WORLD); 
	}
	else{

        //MPI_Barrier(MPI_COMM_WORLD);
			MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"I have received %d in process 1\n",x);
            fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}

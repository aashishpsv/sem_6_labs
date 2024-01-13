#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0){
		//x=10;
		printf("enter number:");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Send(&x,1,MPI_INT,2,1,MPI_COMM_WORLD);
		MPI_Send(&x,1,MPI_INT,3,1,MPI_COMM_WORLD);
		fprintf(stdout,"sent %d from process 0\n",x);
		fflush(stdout);
	}
	else if(rank ==1){
			MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"I have received %d in process %d\n",x,rank);
            fflush(stdout);
	}
	else if(rank ==2){
			MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"I have received %d in process %d\n",x,rank);
            fflush(stdout);
	}
	else if(rank ==3){
			MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"I have received %d in process %d\n",x,rank);
            fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}
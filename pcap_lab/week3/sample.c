#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	int rank,size,N,A[10],B[10],c,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		N=size;
		fprintf(stdout,"enter %d values \n:",N);
		fflush(stdout);
		for(int i=0;i<N;i++){
			scanf("%d",&A[i]);
		}
	}

		MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
		fprintf(stdout,"I haver recived %d from %d\n",c,rank);
		fflush(stdout);
		c=c*c;
		MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
		if(rank ==0){
			fprintf(stdout,"result gathered in root");
			fflush(stdout);
			for(int i=0;i<N;i++) fprintf(stdout,"%d \t",B[i]);
			fflush(stdout);
		}
		printf("\n");
		MPI_Finalize();


}
		

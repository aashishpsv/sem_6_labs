#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	//x=10;
	int total_process=10;
	if(rank==0){
		printf("enter:");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"sent %d from process 0\n",x);
		MPI_Recv(&x,1,MPI_INT,9,1,MPI_COMM_WORLD,&status);
		fprintf(stdout,"recived %d from process 9 to process 0\n",x);
		fflush(stdout); 
	}
	else{
	        if(rank < 9)	
			{   
				//for(int i=1;i<9;i++){
				int i=rank;
			MPI_Recv(&x,1,MPI_INT,(i-1),1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"process  %d recived %d from process %d\n",i,x,i-1);
			x=x+1;
			MPI_Send(&x,1,MPI_INT,i+1,1,MPI_COMM_WORLD);
			fprintf(stdout,"process  %d sent %d to process %d\n",i,x,i+1);
            fflush(stdout);
        //}
            }
            else{
            	int i=rank;
            	MPI_Recv(&x,1,MPI_INT,(i-1),1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"process  %d recived %d from process %d\n",i,x,i-1);
			x=x+1;
			MPI_Send(&x,1,MPI_INT,0,1,MPI_COMM_WORLD);

            }
	}
	MPI_Finalize();
	return 0;
}

#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>


int main(int argc,char *argv[]){
	int rank,size,x;
    int arr[6];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	
	if(rank==0){
		//x=10;
		printf("enter elements:");
		for(int i=0;i<6;i++){
			scanf("%d",&arr[i]);
		}
		int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int);
        char* buffer_attached = (char*)malloc(buffer_attached_size);
        MPI_Buffer_attach(buffer_attached, buffer_attached_size);

		for(int j=1;j<6;j++){
		MPI_Bsend(&arr[j],1,MPI_INT,j,1,MPI_COMM_WORLD);
		fprintf(stdout,"sent %d from process 0 to %d\n",arr[j],j);
        }

		MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
        free(buffer_attached);
		fflush(stdout);
	}
	else if(rank%2==0){
			MPI_Recv(&arr[rank],1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			arr[rank]= arr[rank]*arr[rank];
			fprintf(stdout,"square = %d in process %d\n",arr[rank],rank);
       
       }
    else if(rank%2!=0){
			MPI_Recv(&arr[rank],1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			arr[rank] = arr[rank]*arr[rank]*arr[rank];
			fprintf(stdout,"cube %d in process %d\n",arr[rank],rank);
       
       }

	MPI_Finalize();
	return 0;
}
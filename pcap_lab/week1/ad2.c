#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	 
	 int rank,size,flag,i,j;

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);
	 if(rank==0){
	 	  for (i = 2; i <= 50; i++) 
    {
        flag = 1;
        for (j = 2; j <= i / 2; ++j) 
        { if (i % j == 0) 
            {   flag = 0;
                break;
            }
        }
        if (flag == 1)
            printf("(%d)%d \n",rank, i);
    }

	   }
	 else if(rank==1){
	 	for (i = 51; i <= 100; i++) 
    { 
        flag = 1;
        for (j = 2; j <= i / 2; ++j) 
        { if (i % j == 0) 
            {   flag = 0;
                break;
            }
        }
        if (flag == 1)
            printf("(%d)%d \n",rank, i);
    }
	   }
	  



	 MPI_Finalize();
	 return 0;

}
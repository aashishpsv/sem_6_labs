#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{    
	printf("hello");
	int rank,size,len,no;
	char str[100],str2[100],str3[100];
	MPI_Status status;
    printf("hello");
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("hello");
	if(rank==0){
	printf("enter the string");
		scanf("%s",str);
        len = strlen(str);
        MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Bcast(str,len,MPI_CHAR,0,MPI_COMM_WORLD);
        printf("process 0 recived : %s and repeat is %s",str,str);
        for(int i=1;i<size;i++){
        	MPI_Recv(str2,len*(i+1),MPI_CHAR,i,1,MPI_COMM_WORLD,&status);
        	printf("recived %s from %d",str2,i);

        	//MPI_Recv(no,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
        //	printf("process %d got string %s and repeat is:");
        	//for(int j=0;j<no;j++){
        	//	printf("%s",str);
        	//}
        }
       int final = (size)*(size+1)/2;
        printf("final string is:");
        for(int i=0;i<final;i++){
        	printf("%s",str);
        	
        }

	}


	else{
		int k=0;
		int repeat = len *(rank+1);
			while(k<repeat){
				int l=0;
				while(l < len){
					str2[k]=str[l];
				l++;
					k++;
				}

				MPI_Send(&str2,len*(rank+1),MPI_CHAR,0,1,MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}

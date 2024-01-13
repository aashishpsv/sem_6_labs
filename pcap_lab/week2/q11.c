#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
    int rank,size;
    char str[10];
    char toggle[10];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;

    if(rank == 0){
        printf("enter string");
        scanf("%s",str);
        MPI_Ssend(str, 10, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        fprintf(stdout, "sent %s from process 0 \n", str);
        MPI_Recv(toggle, 10, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        fprintf(stdout, "received %s from process 1", toggle);
        fflush(stdout);
    }
    else{
        MPI_Recv(str, 10, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        fprintf(stdout, "I have received %s in process 1", str);
        for(int i = 0; str[i] != '\0'; i++){
            if(str[i] >= 'A' && str[i] <= 'Z')
                toggle[i] = str[i] + 32; 
            else if(str[i] >= 'a' && str[i] <= 'z')
                toggle[i] = str[i] - 32;
        }
        fprintf(stdout, "sent %s from process 1 \n", toggle);
        MPI_Ssend(toggle, 10, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}

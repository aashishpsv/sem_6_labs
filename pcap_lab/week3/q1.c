#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, N, A[10], B[10], c, i, sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        N = size;
        fprintf(stdout, "Enter %d values:\n", N);
        fflush(stdout);
        for (i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
    }

    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "I have received %d from %d\n", c, rank);
    fflush(stdout);

    int factorial = 1;
    for (i = 1; i <= c; i++) {
        factorial *= i;
    }

    MPI_Gather(&factorial, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        fprintf(stdout, "Result gathered in root:\n");
        fflush(stdout);
        for (i = 0; i < N; i++) {
            sum += B[i];
        }
        fprintf(stdout, "Sum of factorials: %d\n", sum);
        fflush(stdout);
    }

    MPI_Finalize();
}



#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    // Set the size of the array
    N = 16;  // Example array size

    // Allocate memory for the array
    int *inputArray = (int *)malloc(N * sizeof(int));
    int *outputArray = (int *)malloc(N * sizeof(int));

    // Initialize the array in the root process
    if (rank == 0) {
        printf("Input Array: ");
        for (int i = 0; i < N; ++i) {
            inputArray[i] = i + 1;
            printf("%d ", inputArray[i]);
        }
        printf("\n");
    }

    // Broadcast array size to all processes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Allocate memory for local subarrays
    int *localInputArray = (int *)malloc((N / size) * sizeof(int));
    int *localOutputArray = (int *)malloc((N / size) * sizeof(int));

    // Scatter the array to all processes
    MPI_Scatter(inputArray, N / size, MPI_INT, localInputArray, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform the specified operation
    for (int i = 0; i < N / size; ++i) {
        localOutputArray[i] = localInputArray[i] + i * size;
    }

    // Gather the modified subarrays to the root process
    MPI_Gather(localOutputArray, N / size, MPI_INT, outputArray, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process displays the output array
    if (rank == 0) {
        printf("Output Array: ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", outputArray[i]);
        }
        printf("\n");
    }

    // Clean up
    free(inputArray);
    free(outputArray);
    free(localInputArray);
    free(localOutputArray);
    MPI_Finalize();
    return 0;
}
```


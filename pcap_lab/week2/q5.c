#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    // Set the total number of random numbers
    N = size * 3;  // Assume N is evenly divisible by the number of processes

    float *randomNumbers = (float *)malloc(N * sizeof(float));
    float localSum = 0, localSD = 0, globalSum, globalMean, globalSD;

    // Generate random numbers in each process
    srand(rank);  // Seed the random number generator based on the rank
    for (int i = 0; i < N; ++i) {
        randomNumbers[i] = rand() % 50;
        localSum += randomNumbers[i];
    }

    // Gather local sums to calculate global sum
    MPI_Reduce(&localSum, &globalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate global mean
    globalMean = globalSum / N;

    // Calculate local sum of squared differences
    for (int i = 0; i < N; ++i) {
        localSD += pow(randomNumbers[i] - globalMean, 2);
    }

    // Sum local standard deviations to calculate global sum of squared differences
    MPI_Reduce(&localSD, &globalSD, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate standard deviation
    if (rank == 0) {
        globalSD = sqrt(globalSD / N);
        printf("Standard Deviation: %.2f\n", globalSD);
    }

    MPI_Finalize();
    free(randomNumbers);
    return 0;
}

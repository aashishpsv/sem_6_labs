#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATEMENT_LENGTH 1000

int countWords(char *statement) {
    int wordCount = 0;
    char *token = strtok(statement, " ");
    while (token != NULL) {
        wordCount++;
        token = strtok(NULL, " ");
    }
    return wordCount;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    // Root process reads input from file
    if (rank == 0) {
        FILE *file = fopen("input.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        char buffer[MAX_STATEMENT_LENGTH];
        char *statement;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Find text between <TEXT> and </TEXT> tags
            char *startTag = strstr(buffer, "<TEXT>");
            char *endTag = strstr(buffer, "</TEXT>");

            if (startTag != NULL && endTag != NULL && startTag < endTag) {
                int statementLength = endTag - startTag - 6; // 6 is the length of "<TEXT>"
                statement = (char *)malloc((statementLength + 1) * sizeof(char));
                strncpy(statement, startTag + 6, statementLength);
                statement[statementLength] = '\0';

                // Send each statement to a separate process
                for (int i = 1; i < size; i++) {
                    MPI_Send(statement, MAX_STATEMENT_LENGTH, MPI_CHAR, i, 1, MPI_COMM_WORLD);
                }
            }
        }
        fclose(file);
    } else {
        char statement[MAX_STATEMENT_LENGTH];
        MPI_Recv(statement, MAX_STATEMENT_LENGTH, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

        // Count words in the received statement
        int wordCount = countWords(statement);

        // Display word count by each process
        printf("Process %d: Word Count: %d\n", rank, wordCount);

        // Send back the count to the root process
        MPI_Send(&wordCount, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

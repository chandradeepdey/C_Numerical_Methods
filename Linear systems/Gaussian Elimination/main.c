#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "inputlib.h"

int main(void)
{
        fputs("Enter the number of equations to solve: ", stdout);
        const size_t N = (size_t) get_unsigned_long_long(stdin);
        if (N == 0) {
                fputs("Invalid number of equations.\n", stderr);
                exit(EXIT_SUCCESS);
        }

        double (*matrix)[N][N + 1];
        double (*solution)[N];

        if (allocate(N, &matrix, &solution)) {
                fputs("Out of memory.\n", stderr);
                free(matrix);
                free(solution);
                exit(EXIT_FAILURE);
        }

        if (takeInput(N, *matrix)) {
                fputs("Read error.\n", stderr);
                free(matrix);
                free(solution);
                exit(EXIT_FAILURE);
        }

        puts("Here is the augmented matrix:");
        printMatrix(N, *matrix);

        if (triangularMatrix(N, *matrix)) {
                fputs("Cannot solve the system of linear equations.\n", stderr);
                free(matrix);
                free(solution);
                exit(EXIT_FAILURE);
        }

        puts("Here is the matrix after elementary row operations:");
        printMatrix(N, *matrix);

        solve(N, *matrix, *solution);
        free(matrix);

        puts("Here is the solution vector:");
        printSolution(N, *solution);
        free(solution);

        return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char * argv[])
{
        int n;
        double ** matrix;
        double * solution;

        int status = allocate(&matrix, &solution, &n);
        if (status == 1)
                exit(EXIT_FAILURE);
        else if (status == 2) {
                fputs("Quitting program due to invalid number of equations.\n",
                stderr);
                exit(EXIT_SUCCESS);
        }

        if (takeInput(matrix, n)) {
                fputs("Quitting program due to EOF or read error.\n", stderr);
                deallocate(matrix, solution, n);
                exit(EXIT_FAILURE);
        }
        puts("Here is the augmented matrix:");
        printMatrix(matrix, n);

        if (diagonalMatrix(matrix, n)) {
                fputs("Cannot solve the system of linear equations.\n", stderr);
                deallocate(matrix, solution, n);
                exit(EXIT_FAILURE);
        }
        puts("Here is the matrix after elementary row operations:");
        printMatrix(matrix, n);

        solve(matrix, solution, n);
        puts("Here is the solution vector:");
        printSolution(solution, n);

        deallocate(matrix, solution, n);
        return EXIT_SUCCESS;
}

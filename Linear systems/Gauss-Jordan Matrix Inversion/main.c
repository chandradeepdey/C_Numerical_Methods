#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char * argv[])
{
        int n;
        double ** matrix;

        int status = allocate(&matrix, &n);
        if (status == 1)
                exit(EXIT_FAILURE);
        else if (status == 2) {
                fputs("Quitting program due to invalid size of matrix.\n",
                stderr);
                exit(EXIT_SUCCESS);
        }

        if (takeInput(matrix, n)) {
                fputs("Quitting program due to EOF or read error.\n", stderr);
                deallocate(matrix, n);
                exit(EXIT_FAILURE);
        }
        puts("Here is the matrix:");
        printMatrix(matrix, n, 0, n);

        if (diagonalMatrix(matrix, n)) {
                fputs("Cannot produce the inverse matrix.\n", stderr);
                deallocate(matrix, n);
                exit(EXIT_FAILURE);
        }
        puts("Here is the inverse matrix");
        printMatrix(matrix, n, n, 2 * n);

        deallocate(matrix, n);
        return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "inputlib.h"

void printMatrix(double ** matrix, int n, int firstCol, int lastCol)
{
        for (int i = 0; i < n; i++) {
                for (int j = firstCol; j < lastCol; j++)
                        printf("% 8.6g\t", matrix[i][j]);
                putchar('\n');
        }
        putchar('\n');
}

void swap(double ** matrix, int n, int row1, int row2)
{
        double temp;
        int j;
        for (j = 0; j < 2 * n; j++) {
                temp = matrix[row1][j];
                matrix[row1][j] = matrix[row2][j];
                matrix[row2][j] = temp;
        }
}

int diagonalMatrix(double ** matrix, int n)
{
        int i, j, k;
        double multiplier;
        for (i = 0; i < n; i++) {
                if (matrix[i][i] == 0) {
                        for (k = i + 1; k < n; k++) {
                                if (matrix[k][k] != 0)
                                        swap(matrix, n, i, k);
                        }
                        // cannot be solved since diagonal matrix cannot
                        // be formed
                        if (k == n)
                                return 1;
                }
                multiplier = matrix[i][i];
                for (j = i; j < 2 * n; j++)
                        matrix[i][j] /= multiplier;

                for (k = 0; k < n; k++) {
                        if (k == i)
                                continue;
                        multiplier = matrix[k][i];
                        for (j = i; j < 2 * n; j++) {
                                matrix[k][j] -= matrix[i][j] * multiplier;
                        }
                }
        }

        return 0;
}

// allocates an n x n + 1 matrix
// returns 0 if successful
//         1 if out of memory
//         2 if user enters nonpositive n
int allocate(double *** matrix, int * n)
{
        int i;

        fputs("Enter the size of the matrix: ", stdout);
        *n = get_int();
        if (*n <= 0)
                return 2;
        else {
                // allocate an array of double pointers
                *matrix = malloc(*n * sizeof(double *));
                if (*matrix) {
                        // calloc doesn't guarantee NULL pointers, so
                        // manually setting all to NULL after using just malloc
                        for (i = 0; i < *n; i++)
                                (*matrix)[i] = NULL;
                        // each element of the array is actually an array
                        // of doubles instead of just a double pointer
                        for (i = 0; i < *n; i++) {
                                (*matrix)[i] = calloc(2 * *n, sizeof(double));
                                if (!(*matrix)[i])
                                        break;
                        }
                }
                // out of memory while trying to allocate main array
                else {
                        fputs("Out of memory!\n", stderr);
                        return 1;
                }
                // out of memory while trying to allocate individual rows
                if (i != *n) {
                        fputs("Out of memory!\n", stderr);
                        deallocate(*matrix, *n);
                        return 1;
                }

                // everything went fine
                return 0;
        }
}

void deallocate(double ** matrix, int n)
{
        for (int i = 0; i < n; i++)
                free(matrix[i]);
        free(matrix);
}

int takeInput(double ** matrix, int n)
{
        int i, j;
        int digit = (int) log10(n) + 1;

        puts("Please enter the elements of the matrix:");
        for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                        printf("x[%*d][%*d]: ", digit, i + 1, digit, j + 1);
                        matrix[i][j] = get_double();
                }
        }

        // add the identity matrix part
        for (i = 0; i < n; i++) {
                for (j = n; j < 2 * n; j++) {
                        if (i == j - n)
                                matrix[i][j] = 1;
                        else
                                matrix[i][j] = 0;
                }
        }

        if (feof(stdin))
                return 1;
        else
                return 0;
}

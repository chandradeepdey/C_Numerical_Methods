#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "inputlib.h"

void solve(double **matrix, double *solution, int n)
{
        int i, j;

        for (i = n - 1; i >= 0; i--) {
                solution[i] = matrix[i][n];
                for (j = i + 1; j < n; j++)
                        solution[i] -= matrix[i][j] * solution[j];
                solution[i] /= matrix[i][i];
        }
}

/* from this point onwards, i and k are used for rows
 * j is used for columns. the range of j is from 0 through
 * n inclusive, while i and k have the range from 0 through
 * n - 1 inclusive.
 */

void printMatrix(double **matrix, int n)
{
        for (int i = 0; i < n; i++) {
                for (int j = 0; j <= n; j++)
                        printf("% 8.6g\t", matrix[i][j]);
                putchar('\n');
        }
        putchar('\n');
}

void printSolution(const double *solution, int n)
{
        int digit = (int) log10(n) + 1;

        for (int i = 0; i < n; i++)
                printf("x[%*d]: % 8.6g\n", digit, i + 1, solution[i]);
        putchar('\n');
}

void swap(double **matrix, int n, int row1, int row2)
{
        double temp;
        int j;
        for (j = 0; j <= n; j++) {
                temp = matrix[row1][j];
                matrix[row1][j] = matrix[row2][j];
                matrix[row2][j] = temp;
        }
}

int triangularMatrix(double **matrix, int n)
{
        int i, j, k;
        double multiplier;
        for (i = 0; i < n; i++) {
                if (matrix[i][i] == 0) {
                        for (k = i + 1; k < n; k++) {
                                if (matrix[k][k] != 0)
                                        swap(matrix, n, i, k);
                        }
                        // cannot be solved since triangular matrix cannot
                        // be formed
                        if (k == n)
                                return 1;
                }
                for (k = i + 1; k < n; k++) {
                        multiplier = matrix[k][i] / matrix[i][i];
                        for (j = i; j <= n; j++) {
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
int allocate(double ***matrix, double **solution, int *n)
{
        int i;

        fputs("Enter the number of linear equations to solve: ",
        stdout);
        *n = get_int(stdin);
        if (*n <= 0)
                return 2;
        else {
                // allocate an array of double pointers
                *matrix = malloc(*n * sizeof(double*));
                if (*matrix) {
                        // calloc doesn't guarantee NULL pointers, so
                        // manually setting all to NULL after using just malloc
                        for (i = 0; i < *n; i++)
                                (*matrix)[i] = NULL;
                        // each element of the array is actually an array
                        // of doubles instead of just a double pointer
                        for (i = 0; i < *n; i++) {
                                (*matrix)[i] = calloc(*n + 1, sizeof(double));
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
                        deallocate(*matrix, *solution, *n);
                        return 1;
                }

                *solution = calloc(*n, sizeof(double));
                if (!solution) {
                        fputs("Out of memory!\n", stderr);
                        deallocate(*matrix, *solution, *n);
                        return 1;
                }

                // everything went fine
                return 0;
        }
}

void deallocate(double **matrix, double *solution, int n)
{
        for (int i = 0; i < n; i++)
                free(matrix[i]);
        free(matrix);
        free(solution);
}

int takeInput(double **matrix, int n)
{
        int i, j;
        int digit = (int) log10(n) + 1;

        puts("Please enter the coefficients of x[i]");
        for (i = 0; i < n; i++) {
                printf("Equation %*d\n", digit, i + 1);
                for (j = 0; j < n; j++) {
                        printf("x[%*d]: ", digit, j + 1);
                        matrix[i][j] = get_double(stdin);
                }
                printf("y[%*d]: ", digit, i + 1);
                matrix[i][n] = get_double(stdin);
        }
        if (feof(stdin) || ferror(stdin))
                return 1;
        else
                return 0;
}

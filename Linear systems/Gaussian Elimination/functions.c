#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "inputlib.h"

int allocate(size_t N, double (**matrix)[N][N + 1], double (**solution)[N])
{
        *matrix = malloc(sizeof(**matrix));
        *solution = malloc(sizeof(**solution));
        if (*matrix == NULL || *solution == NULL)
                return 1;
        else
                return 0;
}

int takeInput(size_t N, double matrix[N][N + 1])
{
        puts("Please enter the matrix elements one by one.");
        for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < N; ++j) {
                        printf("x[%zd][%zd]: ", i + 1, j + 1);
                        matrix[i][j] = get_double(stdin);
                }
                printf("y[%zd]: ", i + 1);
                matrix[i][N] = get_double(stdin);
        }

        if (feof(stdin) || ferror(stdin))
                return 1;
        else
                return 0;
}

void printMatrix(size_t N, const double matrix[N][N + 1])
{
        for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j <= N; ++j)
                        printf("% 8.6g\t", matrix[i][j]);
                putchar('\n');
        }
        putchar('\n');
}

int triangularMatrix(size_t N, double matrix[N][N + 1])
{
        double multiplier;
        for (size_t i = 0; i < N; ++i) {
                // find a new row if pivot is zero
                if (matrix[i][i] == 0) {
                        size_t k = i + 1;
                        while (k < N) {
                                if (matrix[k][k] != 0)
                                        swap(N, matrix, i, k);
                                ++k;
                        }
                        // cannot be solved since triangular matrix cannot
                        // be formed
                        if (k == N)
                                return 1;
                }
                for (size_t k = i + 1; k < N; ++k) {
                        multiplier = matrix[k][i] / matrix[i][i];
                        for (size_t j = i; j <= N; ++j) {
                                matrix[k][j] -= matrix[i][j] * multiplier;
                        }
                }
        }

        return 0;
}

void swap(size_t N, double matrix[N][N + 1], size_t row1, size_t row2)
{
        double temp;
        for (size_t j = 0; j <= N; ++j) {
                temp = matrix[row1][j];
                matrix[row1][j] = matrix[row2][j];
                matrix[row2][j] = temp;
        }
}

void solve(size_t N, const double matrix[N][N + 1], double solution[N])
{
        size_t i = N;
        while (i > 0) {
                --i; // from i == N - 1 to i == 0, do this because unsigned

                solution[i] = matrix[i][N];
                for (size_t j = i + 1; j < N; ++j)
                        solution[i] -= matrix[i][j] * solution[j];
                solution[i] /= matrix[i][i];
        }
}

void printSolution(size_t N, const double solution[N])
{
        for (size_t i = 0; i < N; ++i)
                printf("x[%zd]: % 8.6g\n", i + 1, solution[i]);
        putchar('\n');
}

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int allocate(size_t N, double (**matrix)[N][N + 1], double (**solution)[N]);
int takeInput(size_t N, double matrix[N][N + 1]);
void printMatrix(size_t N, const double matrix[N][N + 1]);
int triangularMatrix(size_t N, double matrix[N][N + 1]);
void solve(size_t N, const double matrix[N][N + 1], double solution[N]);
void printSolution(size_t N, const double solution[N]);

#endif

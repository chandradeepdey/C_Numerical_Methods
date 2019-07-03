#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int allocate(double *** matrix, double ** solution, int * n);
void deallocate(double ** matrix, double * solution, int n);
int takeInput(double ** matrix, int n);
int diagonalMatrix(double ** matrix, int n);
void swap(double ** matrix, int n, int row1, int row2);
void solve(double ** matrix, double * solution, int n);
void printMatrix(double ** matrix, int n);
void printSolution(const double * solution, int n);

#endif

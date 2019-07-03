#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

int allocate(double *** matrix, int * n);
void deallocate(double ** matrix, int n);
int takeInput(double ** matrix, int n);
int diagonalMatrix(double ** matrix, int n);
void swap(double ** matrix, int n, int row1, int row2);
void printMatrix(double ** matrix, int n, int firstCol, int lastCol);

#endif

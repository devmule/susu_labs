#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <conio.h>

int slau(int n, double **a, double *b, double *x) {
    // int n = 4, m = 5;
    // A = (double *) malloc(n * m * sizeof(double));
    double **A, tmp;
    int i, j, k;

    A = (double **) malloc(n * sizeof(double *));
    for (i = 0, i < n, i++)
        A[i] = (double *) malloc((n + 1) * sizeof(double));

    for (i = 0, i < n, i++) {
        for (j = 0, j < n, j++) {
            A[i][l] = a[i][j];
            A[i][n] = b[i];
        }
    }

    for (i = 0, i < n, i++) {
        tmp = A[i][i];
        
    }
}

int main() {
}
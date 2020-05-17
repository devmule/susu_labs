#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
int lms(int n, int p, double *x, double *y, double *c);
n – количество узлов,
р – порядок полинома,
х, у – абсциссы и ординаты узлов,
с – коэффициенты.
Возвращаемое значение:
1 – коэффициенты вычислены,
0 – коэффициенты не вычислены.
*/
int lms(int n, int p, double *x, double *y, double *c) {
    double **a;
    double *v;
    int i, j, k, res;
    a = (double **) malloc(p * sizeof(double *));
    v = (double *) malloc(k);
    for (i = 0; i < p; i++) a[i] = (double *) malloc(p * sizeof(double));
    for (i = 0; i < p; i++) {
        v[i] = 0;
        for (j = 0; j < p; j++)
            a[i][j] = 0;
    }
    for (i = 0; i < p; i++)
        for (j = 0; j < p; j++)
            for (k = 0; k < n; k++)
                a[i][j] += pow(x[k], (i + j));
    for (i = 0; i < p; i++)
        for (k = 0; k < n; k++)
            v[i] += pow(x[k], i) * y[k];
    res = slau(a, v, c);
    for (i = 0; i < p; i++)
        free(a[i]);
    free(a);
    free(v);
    return res;
}

double f(x) { return .5 * x * x * x + 2 * x * x + 4 * x + 11; }

int main() {
    // Батятин Максим
    // Вариант №3
    int n = 10;
    int p = 4;
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    double *c = (double *) malloc(p * sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = i;
        y[i] = f(i);
    }

    if (lms(n, p, x, y, c)) {
        printf("\ndone!");
    } else {
        printf("\nerror!");
    }

    return 0;
}

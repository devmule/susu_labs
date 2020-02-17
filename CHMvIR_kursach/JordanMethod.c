#include <stdio.h>
#include <stdlib.h>

void print_matrix(int n, double *a) {
    for (int i = 0; i < n * n; ++i) {
        printf("%f", a[i]);
        printf("%s", ",");
        if ((i + 1) % n == 0) printf("%s", "\n");
    }
}

void check_multiply(int n, const double *a, const double *b) {
    double tmp;
    for (int i = 0; i < n; ++i) { // стролбец
        for (int j = 0; j < n; ++j) { // строка
            tmp = 0; // строка первого на столбец второго
            for (int k = 0; k < n; ++k) tmp += a[j * n + k] * b[k * n + i];
            printf("%f", tmp);
            printf("%s", ",");
        }
        printf("%s", "\n");
    }
}

int invmatr(int n, const double *a, double *b) {
    double *x = (double *) malloc(n * n * sizeof(double));
    for (int i = 0; i < n * n; i++) {
        x[i] = a[i];
        b[i] = i % (n + 1) == 0 ? 1.0 : 0.0;
    }

    double tmp;
    for (int k = 0; k < n; k++) {
        tmp = x[k * n + k]; // разрешающий элемент
        if (tmp == 0) return 0; // проверка на вырожденность
        for (int j = 0; j < n; j++) {
            x[k * n + j] /= tmp;
            b[k * n + j] /= tmp;
        }
        for (int i = k + 1; i < n; i++) {
            tmp = x[i * n + k];
            for (int j = 0; j < n; ++j) {
                x[i * n + j] -= x[k * n + j] * tmp;
                b[i * n + j] -= b[k * n + j] * tmp;
            }
        }
    }
    for (int k = n - 1; k > 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            tmp = x[i * n + k]; // разрешающий элемент, проверка не нужна, т.к. диагональ уже единичная
            for (int j = 0; j < n; ++j) {
                x[i * n + j] -= x[k * n + j] * tmp;
                b[i * n + j] -= b[k * n + j] * tmp;
            }
        }
    }
    return 1;
}

int main() {
    FILE *input_file = fopen("C:\\Users\\79227\\Desktop\\susu_labs\\CHMvIR_kursach\\input1.txt", "r");
    if (input_file == NULL) return 0;

    int n;
    printf("%s", "write n: ");
    n = (int) getchar() - 48; // ASCII символы - цифры стартуют с 48

    double *A, *B, *X;
    A = (double *) malloc(n * n * sizeof(double));
    B = (double *) malloc(n * n * sizeof(double));
    X = (double *) malloc(n * n * sizeof(double));
    for (int i = 0; i < n * n; i++) fscanf(input_file, "%lf", &A[i]);
    for (int i = 0; i < n * n; i++) fscanf(input_file, "%lf", &B[i]);
    fclose(input_file);

    if (invmatr(n, A, X)) {
        printf("%s", "\nmatrix A inverted successfully:\n");
        print_matrix(n, A);

        printf("%s", "\nmatrices multiply check:\n");
        check_multiply(n, A, X);
    } else {
        printf("%s", "\ncannot invert matrix A\n");
    };

    if (invmatr(n, B, X)) {
        printf("%s", "\nmatrix B inverted successfully:\n");
        print_matrix(n, B);

        printf("%s", "\nmatrices multiply check:\n");
        check_multiply(n, B, X);
    } else {
        printf("%s", "\ncannot invert matrix B\n");
    };

    return 0;
}

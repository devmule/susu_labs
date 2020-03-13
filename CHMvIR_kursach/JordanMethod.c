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

double det(int n, const double *a) {
    double d = 0;
    double tmp_plus, tmp_minus;
    for (int i = 0; i < n; i++) {
        tmp_plus = tmp_minus = 1;
        for (int j = 0; j < n; j++) {
            tmp_plus *= a[j * n + (i + j) % n];
            tmp_minus *= a[j * n + (n + i - j) % n];
        }
        d += tmp_plus - tmp_minus;
    }
    printf("%f", d);
    return d;
}

int invmatr(int n, const double *a, double *b) {
    if (det(n, a) == 0.0) return 0;

    double *x = (double *) malloc(n * n * sizeof(double));
    for (int i = 0; i < n * n; i++) { // представляем расширенную матрицу как две обычные матрицы
        x[i] = a[i]; // копия матрицы a, т.к. исходную менять нельзя, эта матрица будет левой частью
        b[i] = i % (n + 1) == 0 ? 1.0 : 0.0; // правая часть "расширенной матрицы"
    }

    double tmp;
    for (int k = 0; k < n; k++) { // для каждой строки
        tmp = x[k * n + k]; // находим разрешающий элемент
        if (tmp == 0) return 0; // проверка на вырожденность
        for (int j = 0; j < n; j++) {
            x[k * n + j] /= tmp;
            b[k * n + j] /= tmp;
        } // делим строку на число, равное элементу на диагонали, чтобы находящийся на диагонали элемент был равен "1"

        for (int i = k + 1; i < n; i++) { // для каждой строки ниже текущей
            tmp = x[i * n + k]; // находим разрешающий элемент
            for (int j = 0; j < n; ++j) {
                x[i * n + j] -= x[k * n + j] * tmp;
                b[i * n + j] -= b[k * n + j] * tmp;
            }// вычитаем из под-строки строку, над которой работаем сейчас, домноженную на tmp,
            // чтобы все элементы ниже разрешающего стали равны нулю
        }
    }
    for (int k = n - 1; k > 0; k--) { // обратный ход, избавляемя от не-нулей выше главной диагонали
        for (int i = k - 1; i >= 0; i--) {
            tmp = x[i * n + k]; // разрешающий элемент
            for (int j = 0; j < n; ++j) {
                x[i * n + j] -= x[k * n + j] * tmp;
                b[i * n + j] -= b[k * n + j] * tmp;
            }
        }
    }
    return 1;
}

int main() {
    FILE *input_file = fopen("..\\input1.txt", "r");
    if (input_file == NULL) return 0;

    int n;
    printf("%s", "write n: ");
    scanf("%d", &n);

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

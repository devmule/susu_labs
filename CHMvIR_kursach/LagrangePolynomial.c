#include <stdio.h>
#include <stdlib.h>

double lagr(int n, double *xt, double *yt, double x) {
    double lagr_pol = 0;
    double basics_pol;

    for (int i = 0; i < n; i++) {
        basics_pol = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            basics_pol *= (x - xt[j]) / (xt[i] - xt[j]);
        }
        lagr_pol += basics_pol * yt[i];
    }
    return lagr_pol;
}

int main(void) {
    const int size = 8;
    double *xt = (double *) malloc(size * sizeof(double));
    double *yt = (double *) malloc(size * sizeof(double));

    FILE *input_file = fopen("C:\\Users\\79227\\Desktop\\susu_labs\\CHMvIR_kursach\\input2.txt", "r");
    if (input_file == NULL) return 0;
    for (int i = 0; i < size; i++) {
        fscanf(input_file, "%lf", &xt[i]);
        fscanf(input_file, "%lf", &yt[i]);
    }
    fclose(input_file);

    for (double j = 0; j <= 7; j += 0.1) {
        printf("%lf : %lf\n", j, lagr(size, xt, yt, j));
    }

    return 0;
}

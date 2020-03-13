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

    FILE *input_file = fopen("..\\input2.txt", "r");
    FILE *output_file = fopen("..\\output2.txt", "w");
    if (input_file == NULL || output_file == NULL) return 0;

    for (int i = 0; i < size; i++) {
        fscanf(input_file, "%lf", &xt[i]);
        fscanf(input_file, "%lf", &yt[i]);
    }
    fclose(input_file);

    double y;
    for (double x = 0; x < 7; x += 0.1) {
        y = lagr(size, xt, yt, x);
        printf("%lf : %lf\n", x, y);
        fprintf(output_file, "%lf : %lf\n", x, y);
    }

    return 0;
}

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

double f(double x) {
    // функция для примера
    // 2*x^4 + 3*x^3 - x^2 + 4
    return 2 * x * x * x * x + 3 * x * x * x - x * x + 4;
}

int main(void) {
    // Батятин Максим
    // Вариант №3
    const int size = 10; // количество координат в табличной функции
    double *xt = (double *) malloc(size * sizeof(double));
    double *yt = (double *) malloc(size * sizeof(double));

    // задание табличной функции по функции для примера
    for (int i = 0; i < size; i++) {
        xt[i] = i;
        yt[i] = f(i);
    }

    // проходим по точкам, не включенным в таблицу
    // сравниваем полученное интерполяцией значение табличной функции
    // со значением функции f(x) в этой же точке
    printf("coord   :\tinterpolation,\tf(x) func\n");
    double y, x = 0.0; // от 0
    for (;;) {
        if (x > 7) break; // до 7 включительно
        else {
            y = lagr(size, xt, yt, x); // расчитываем значение у, интерполируя табличную функцию
            // выводим в консоль значение, найденное интерполяцией табличной функции и значение f(x) в координате x
            printf("%f:\t%lf,\t%lf\n", x, y, f(x));
            x += 0.1; // с шагом 0.1
        }
    }
    return 0;
}

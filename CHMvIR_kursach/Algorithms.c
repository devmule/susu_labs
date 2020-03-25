#include <stdio.h>
#include <math.h>

//========= метод простой итерации ==========================
double simpleIterationMethod(double (*f)(double), double x0, const double eps) {
    // fixme
    // можно сделать проверку на дельту - если дельта
    //  в новой итерации больше, чем в предыдущей, то завершить цикл с ошибкой
    double x1;
    for (;;) {
        x1 = f(x0);
        if (fabs(x1 - x0) < eps) break;
        x0 = x1;
    }
    return x1;
}

//========= метод Ньютона ==========================
double newtonMethod(double (*f)(double), double (*df)(double), double x0, const double eps) {
    double x1; // текущее значение для проверки
    for (;;) {
        x1 = x0 - f(x0) / df(x0);
        if (fabs(x1 - x0) < eps) break;
        x0 = x1;
    }
    return x1;
}

//========= метод секущих ==========================
double secantMethod(double (*f)(double), double x0, double x1, double eps) {
    double res, y;
    // todo доделать
    do {
        y = res;
        res = x1 - ((x1 - x0) / (f(x1) - f(x0))) * f(x1);
        x0 = x1;
        x1 = res;
    } while (fabs(y - res) >= eps);
    return 0;
}

double f1(double x) { return x / 2 + 5; }

double df1(double x) { return .5; }

int main() {
    printf("x=%f\n", simpleIterationMethod(f1, 1.5, 1E-10));
    printf("x=%f\n", newtonMethod(f1, df1, 1.5, 1E-10));
    printf("x=%f\n", secantMethod(f1, 3, 9, 1E-10));
    return 0;
}
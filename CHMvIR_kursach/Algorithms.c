#include <stdio.h>
#include <math.h>

//========= метод простой итерации ==========================
double simpleIterationMethod(double (*f)(double), double x0, const double eps) {
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

//========= метод бисекции ==========================
double bisectionMethod(double (*f)(double), double a, double b, const double eps) {
    double c;
    // f(a) и f(b) должны быть разных знаков
    if (f(a) * f(b) < 0) {
        for (;;) {
            c = (a + b) / 2.0;
            if (f(a) * f(c) > 0) a = c;
            else b = c;
            if (fabs(f(a) - f(b)) / 2 < eps) break;
        }
        return c;
    }
}

//========= метод секущих ==========================
double secantMethod(double (*f)(double), double x0, double x1, double eps) {
    // работает только если выполняется условие  ' f(x0) * f(x1) < 0 '
    // сдвигать будем только одну сторону, другую рассчитаем заранее
    double y1, y0 = f(x0) / x0;
    for (;;) {
        y1 = f(x1) / x1;
        x1 = x1 - (y1 / (y1 - y0)) * (x1 - x0);
        if (fabs(f(x1)) < eps) break;
    }
    return x1;
}


//========= функции ==========================
double f2(double x) { return 1 / x - sin(3.1415926535 * x / 180); } //Сама функция f(x)

double fx2(double x) {
    return 1 / (sin(3.1415926535 * x / 180));
} //x=A(x), где A(x) - это f(x)=A(x)-x, т.е. тупо выражаем x

double df2(double x) { return 1 / pow(x, 2) - (cos(3.1415926535 * x / 180)); } //Производная f(x) для метода Ньютона

double f1(double x) { return x / 2 + 5; }

double df1(double x) { return .5; }

int main() {
    printf("x=%f\n", simpleIterationMethod(fx2, 1.5, 1E-10)); // x=7.580454
    printf("x=%f\n", newtonMethod(f2, df2, 1.5, 1E-10)); // x=7.580454
    printf("x=%f\n", bisectionMethod(f2, -20, 23, 1E-10)); // x=7.580454
    printf("x=%f\n", secantMethod(f2, 1, 10, 1E-10)); // x=7.580454
    return 0;
}
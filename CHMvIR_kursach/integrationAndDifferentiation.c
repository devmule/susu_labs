#include <stdio.h>
#include <math.h>

// 1. Численное интегрирование
// 1.1. Методы прямоугольников
double rectangleMethod(double a, double b, double f(double), int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += f(a + (b - a) * i / n);
    return (b - a) / n * sum;
}

// 1.2. Метод трапеций
double trapezeMethod(double a, double b, double f(double), int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x1 = a + (b - a) * i / n;
        double x2 = a + (b - a) * (i + 1) / n;
        sum += (f(x1) + f(x2)) * (x2 - x1) / 2;
    }
    return sum;
}

// 1.3. Квадратурные формулы
double SimpsonMethod(double a, double b, double f(double), int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x1 = a + (b - a) * i / n;
        double x2 = a + (b - a) * (i + 1) / n;
        sum += (x2 - x1) / 6.0 * (f(x1) + 4.0 * f(0.5 * (x1 + x2)) + f(x2));
    }
    return sum;
}


double f(double x) {
    return sin(x);
}

int main() {
    // Батятин Максим
    // Вариант №3

    // настоящий интеграл для sin(x) от 0 до 2 = 1.41614683654714
    printf("integral=%f\n", rectangleMethod(0, 2, f, 100)); // integral=1.415237
    printf("integral=%f\n", trapezeMethod(0, 2, f, 100)); // integral=1.414327
    printf("integral=%f\n", SimpsonMethod(0, 2, f, 100)); // integral=1.416147
    return 0;
}
// Лабораторна робота №1 — варіант 9
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    cout << "ЛР №1, варіант 9\n";
    cout << "Завдання 1. Обчислення виразу\n";
    double A, B, C, D;
    cout << "Введіть A, B, C, D: ";
    if (!(cin >> A >> B >> C >> D)) return 1;

    // Формула з таблиці: X = (A^2-B^2)(C-D) / sqrt(e(A^2-B^2)).
    double radicand = exp(1.0) * (A * A - B * B);
    if (radicand < 0.0 || (radicand == 0.0)) {
        cout << "Вираз не визначений для введених значень.\n";
    } else {
        double X = (A * A - B * B) * (C - D) / sqrt(radicand);
        cout << setprecision(10) << "X = " << X << "\n";
    }

    cout << "\nЗавдання 2. Об'єм тора\n";
    double r, R;
    cout << "Введіть внутрішній радіус r та зовнішній радіус R: ";
    if (!(cin >> r >> R)) return 1;
    if (r < 0 || R <= r) {
        cout << "Помилка: потрібно 0 <= r < R.\n";
    } else {
        // V = (pi^2 / 4) * (R + r) * (R - r)^2
        const double pi = acos(-1.0);
        double V = (pi * pi / 4.0) * (R + r) * (R - r) * (R - r);
        cout << setprecision(10) << "Об'єм тора V = " << V << "\n";
    }
    return 0;
}

// Лабораторна робота №2 — варіант 9
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << "ЛР №2, варіант 9\n";
    cout << "Завдання 1. Обчислення кусочно заданої функції\n";
    double x, b, c;
    cout << "Введіть x, b, c: ";
    if (!(cin >> x >> b >> c)) return 1;

    if (x > 0 && b != c) {
        cout << "f(x) = " << (2.0 * x * x / (b - c)) << "\n";
    } else if (x > 0 && b == c) {
        if (fabs(1.0 + x) < 1e-12) cout << "Функція не визначена.\n";
        else cout << "f(x) = " << ((1.0 - x) / (1.0 + x)) << "\n";
    } else if (x < 0) {
        cout << "f(x) = " << ((b + c) * x * x) << "\n";
    } else {
        cout << "Функція не визначена для x = 0 (за умовою варіанта).\n";
    }

    cout << "\nЗавдання 2. Кількість однакових і різних чисел\n";
    double a, d, e;
    cout << "Введіть три дійсних числа: ";
    if (!(cin >> a >> d >> e)) return 1;
    int distinct;
    if (a == d && d == e) distinct = 1;
    else if (a == d || a == e || d == e) distinct = 2;
    else distinct = 3;
    cout << "Кількість різних чисел: " << distinct << "\n";
    cout << "Кількість однакових чисел (значень, що повторюються): "
         << (3 - distinct) << "\n";
    if (distinct == 1) cout << "Усі три числа однакові.\n";
    else if (distinct == 2) cout << "Два числа однакові, одне відрізняється.\n";
    else cout << "Усі три числа різні.\n";
    return 0;
}

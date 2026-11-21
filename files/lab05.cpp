// Лабораторна робота №5, варіант 9
// Задача Йосипа: кожна друга людина вибуває з кола.
#include <iostream>
using namespace std;

int josephusRecursive(int n) {
    if (n == 1) return 1;
    return (josephusRecursive(n - 1) + 1) % n + 1;
}

int josephusIterative(int n, long long &iterations) {
    int survivor = 0;
    for (int i = 1; i <= n; ++i) {
        survivor = (survivor + 2) % i;
        ++iterations;
    }
    return survivor + 1;
}

int main() {
    int n;
    cout << "Enter initial number of people n: ";
    if (!(cin >> n) || n < 1) return 1;
    int current = n, rounds = 0;
    cout << "Round | people | recursive | iterative\n";
    while (current > 1) {
        long long iterations = 0;
        int r = josephusRecursive(current);
        int it = josephusIterative(current, iterations);
        cout << ++rounds << "     | " << current << "      | " << r
             << "         | " << it << "\n";
        current = r;
    }
    cout << "Final survivor number: 1\n";
    cout << "Number of repeated procedures: " << rounds << "\n";
    cout << "Note: the iterative version uses " << n
         << " loop iterations in the first round; recursion depth is n.\n";
}

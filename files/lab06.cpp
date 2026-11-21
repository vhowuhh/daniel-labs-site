// Лабораторна робота №6, варіант 9
// 9.1: масив НСД відповідних елементів; 9.2: insertion sort + exponential search.
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int gcdEuclid(int a, int b) {
    a = abs(a); b = abs(b);
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}
vector<int> readArray(int n, const string& name) {
    vector<int> a(n);
    int mode;
    cout << name << ": 1 - keyboard, 2 - random: "; cin >> mode;
    if (mode == 1) {
        for (int &x : a) cin >> x;
    } else {
        int lo, hi; cout << "Random range [lo hi]: "; cin >> lo >> hi;
        if (lo > hi) swap(lo, hi);
        for (int &x : a) x = lo + rand() % (hi - lo + 1);
    }
    return a;
}
void print(const vector<int>& a) { for (int x : a) cout << x << ' '; cout << '\n'; }
int exponentialSearch(const vector<int>& a, int key) {
    if (a.empty()) return -1;
    if (a[0] == key) return 0;
    size_t bound = 1;
    while (bound < a.size() && a[bound] < key) bound *= 2;
    size_t left = bound / 2, right = min(bound, a.size() - 1);
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (a[mid] == key) return (int)mid;
        if (a[mid] < key) left = mid + 1;
        else { if (mid == 0) break; right = mid - 1; }
    }
    return -1;
}
int main() {
    srand((unsigned)time(nullptr));
    cout << "Task 9.1\nEnter lengths of arrays A and B: ";
    int n, m; cin >> n >> m;
    if (n < 0 || m < 0) return 1;
    auto a = readArray(n, "Array A"); auto b = readArray(m, "Array B");
    vector<int> c(min(n, m));
    for (size_t i = 0; i < c.size(); ++i) c[i] = gcdEuclid(a[i], b[i]);
    cout << "A: "; print(a); cout << "B: "; print(b); cout << "GCD array (common positions): "; print(c);
    cout << "\nTask 9.2\nEnter array length: ";
    int k; cin >> k; if (k < 0) return 1;
    auto v = readArray(k, "Array");
    cout << "Initial: "; print(v);
    for (size_t i = 1; i < v.size(); ++i) {
        int key = v[i]; int j = (int)i - 1;
        while (j >= 0 && v[j] > key) { v[j + 1] = v[j]; --j; }
        v[j + 1] = key;
        cout << "After insertion " << i << ": "; print(v);
    }
    int key; cout << "Value to search: "; cin >> key;
    int pos = exponentialSearch(v, key);
    if (pos >= 0) cout << "Found at zero-based index " << pos << '\n';
    else cout << "Not found\n";
}

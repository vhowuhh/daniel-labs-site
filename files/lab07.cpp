// Лабораторна робота №7, варіант 9
// 9.1: Shell sort стовпців за першим рядком; 9.2: добуток прямокутних матриць.
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
using Matrix = vector<vector<double>>;
void print(const Matrix& a) { for (auto& row : a) { for (double x : row) cout << setw(9) << x; cout << '\n'; } }
Matrix makeMatrix(int r, int c) {
    Matrix a(r, vector<double>(c)); int mode;
    cout << "1 - keyboard, 2 - random: "; cin >> mode;
    if (mode == 1) for (auto& row : a) for (double& x : row) cin >> x;
    else { int lo, hi; cout << "Random range: "; cin >> lo >> hi; if(lo>hi) swap(lo,hi); for(auto& row:a) for(double& x:row) x=lo+rand()%(hi-lo+1); }
    return a;
}
void shellSortColumns(Matrix& a) {
    int n = (int)a[0].size();
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; ++i) {
            int j = i;
            while (j >= gap && a[0][j-gap] > a[0][j]) {
                for (auto& row : a) swap(row[j], row[j-gap]);
                j -= gap;
            }
        }
}
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c(a.size(), vector<double>(b[0].size(), 0));
    for(size_t i=0;i<a.size();++i) for(size_t k=0;k<b.size();++k) for(size_t j=0;j<b[0].size();++j) c[i][j]+=a[i][k]*b[k][j];
    return c;
}
int main(){
    srand((unsigned)time(nullptr));
    cout << "Task 9.1: enter m,n (>3): "; int m,n; cin>>m>>n; if(m<=3||n<=3)return 1;
    Matrix a=makeMatrix(m,n); cout<<"Input matrix:\n"; print(a); shellSortColumns(a); cout<<"Columns sorted by first row:\n"; print(a);
    cout << "\nTask 9.2: number of matrices k (>=3): "; int k; cin>>k; if(k<3)return 1;
    vector<Matrix> matrices; int rows, cols;
    cout << "Rows and columns of matrix 1: "; cin>>rows>>cols; if(rows<1||cols<1)return 1;
    matrices.push_back(makeMatrix(rows,cols));
    for(int i=2;i<=k;++i){ int r,c; cout<<"Rows and columns of matrix "<<i<<": "; cin>>r>>c; if(r<1||c<1)return 1; if(cols!=r){cout<<"Incompatible dimensions: product cannot be calculated.\n";return 0;} matrices.push_back(makeMatrix(r,c)); cols=c; }
    Matrix result=matrices[0];
    for(int i=1;i<k;++i){ result=multiply(result,matrices[i]); cout<<"Intermediate product after matrix "<<i+1<<":\n"; print(result); }
    cout<<"Final product:\n"; print(result);
}

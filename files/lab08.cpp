#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

// ЛР №8, варіант 29 -> варіант 5 (24 варіанти): транспонування розрідженої матриці.
// Матриця зберігається у форматі CSR: AN — значення, JA — стовпці, IA — початки рядків.
struct CSRMatrix { int rows, cols, nnz; double* AN; int* JA; int* IA; };

void freeCSR(CSRMatrix& a) { delete[] a.AN; delete[] a.JA; delete[] a.IA; a = {0,0,0,nullptr,nullptr,nullptr}; }
CSRMatrix denseToCSR(double** d, int r, int c) {
    CSRMatrix a{r,c,0,nullptr,nullptr,nullptr};
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) if(d[i][j]!=0) ++a.nnz;
    a.AN = new double[a.nnz]; a.JA = new int[a.nnz]; a.IA = new int[r+1];
    int k=0;
    for(int i=0;i<r;i++){ a.IA[i]=k; for(int j=0;j<c;j++) if(d[i][j]!=0){a.AN[k]=d[i][j];a.JA[k]=j;++k;} }
    a.IA[r]=k; return a;
}
double** allocateDense(int r,int c){ double** d=new double*[r]; for(int i=0;i<r;i++){d[i]=new double[c]();} return d; }
void freeDense(double** d,int r){if(!d)return;for(int i=0;i<r;i++)delete[] d[i];delete[] d;}
void printDense(double** d,int r,int c){for(int i=0;i<r;i++){for(int j=0;j<c;j++)cout<<setw(6)<<d[i][j];cout<<'\n';}}
void printCSR(const CSRMatrix& a){
    cout<<"AN: ";for(int i=0;i<a.nnz;i++)cout<<a.AN[i]<<' ';cout<<"\nJA: ";for(int i=0;i<a.nnz;i++)cout<<a.JA[i]<<' ';cout<<"\nIA: ";for(int i=0;i<=a.rows;i++)cout<<a.IA[i]<<' ';cout<<'\n';
}
CSRMatrix transposeCSR(const CSRMatrix& a){
    CSRMatrix t{a.cols,a.rows,a.nnz,nullptr,nullptr,nullptr};
    t.AN=new double[t.nnz];t.JA=new int[t.nnz];t.IA=new int[t.rows+1]();
    for(int k=0;k<a.nnz;k++)++t.IA[a.JA[k]+1];
    for(int i=1;i<=t.rows;i++)t.IA[i]+=t.IA[i-1];
    int* next=new int[t.rows];for(int i=0;i<t.rows;i++)next[i]=t.IA[i];
    for(int i=0;i<a.rows;i++)for(int k=a.IA[i];k<a.IA[i+1];k++){
        int row=a.JA[k], pos=next[row]++;t.AN[pos]=a.AN[k];t.JA[pos]=i;
    }
    delete[] next;return t;
}
double** transposeDense(double** d,int r,int c){double** t=allocateDense(c,r);for(int i=0;i<r;i++)for(int j=0;j<c;j++)t[j][i]=d[i][j];return t;}
void generate(CSRMatrix& a,double*** denseOut){
    freeCSR(a);int r,c;cout<<"Кількість рядків і стовпців (1..20): ";cin>>r>>c;
    if(!cin||r<1||c<1||r>20||c>20){cin.clear();cin.ignore(10000,'\n');cout<<"Некоректні розміри.\n";return;}
    double** d=allocateDense(r,c);int total=r*c, nonzero=0;
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){if(rand()%10<3){d[i][j]=1+rand()%9;nonzero++;}}
    // Гарантуємо понад 60% нульових елементів.
    while(nonzero>total*0.4){int i=rand()%r,j=rand()%c;if(d[i][j]!=0){d[i][j]=0;--nonzero;}}
    a=denseToCSR(d,r,c);*denseOut=d;cout<<"Згенерована матриця ("<<r<<"x"<<c<<"), нульових елементів: "<<total-nonzero<<" з "<<total<<".\n";printDense(d,r,c);
}
void showMatrix(CSRMatrix& a,double**& d){if(!d){cout<<"Спочатку згенеруйте матрицю.\n";return;}cout<<"Початкова матриця:\n";printDense(d,a.rows,a.cols);cout<<"CSR-представлення:\n";printCSR(a);}
void compareTranspose(CSRMatrix& a,double**& d){
    if(!d){cout<<"Спочатку згенеруйте матрицю.\n";return;}
    using clk=chrono::high_resolution_clock;
    auto s1=clk::now();CSRMatrix t=transposeCSR(a);auto e1=clk::now();
    auto s2=clk::now();double** td=transposeDense(d,a.rows,a.cols);auto e2=clk::now();
    cout<<"Транспонована матриця (CSR):\n";double** check=allocateDense(t.rows,t.cols);
    for(int i=0;i<t.rows;i++)for(int k=t.IA[i];k<t.IA[i+1];k++)check[i][t.JA[k]]=t.AN[k];printDense(check,t.rows,t.cols);
    cout<<"CSR-масиви транспонованої матриці:\n";printCSR(t);
    cout<<"Транспонована матриця (звичайний алгоритм):\n";printDense(td,a.cols,a.rows);
    cout<<fixed<<setprecision(3)<<"Час CSR: "<<chrono::duration<double,micro>(e1-s1).count()<<" мкс\nЧас звичайного алгоритму: "<<chrono::duration<double,micro>(e2-s2).count()<<" мкс\n";
    size_t csrBytes=t.nnz*(sizeof(double)+sizeof(int))+(t.rows+1)*sizeof(int);size_t denseBytes=(size_t)t.rows*t.cols*sizeof(double);
    cout<<"Пам'ять CSR: "<<csrBytes<<" байт; звичайна матриця: "<<denseBytes<<" байт\n";
    freeCSR(t);freeDense(td,a.cols);freeDense(check,t.rows);
}
int main(){srand((unsigned)time(nullptr));CSRMatrix a{0,0,0,nullptr,nullptr,nullptr};double** dense=nullptr;
    using Action=void(*)(CSRMatrix&,double**&);
    Action actions[]={showMatrix,compareTranspose};
    int choice;
    do{cout<<"\n=== Лабораторна робота №8 ===\n1. Згенерувати розріджену матрицю\n2. Вивести матрицю та CSR-масиви\n3. Транспонувати й порівняти алгоритми\n0. Вихід\nВаш вибір: ";cin>>choice;
        if(choice==1){freeDense(dense,a.rows);dense=nullptr;generate(a,&dense);}else if(choice==2||choice==3)actions[choice-2](a,dense);else if(choice!=0)cout<<"Невірний пункт меню.\n";
    }while(choice!=0);
    int oldRows=a.rows;freeCSR(a);freeDense(dense,oldRows);return 0;
}

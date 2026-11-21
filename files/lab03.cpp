// Лабораторна робота №3, варіант 9.
// Подвійна сума: x=1..5, k=0..inf. За зображенням знаменник трактовано
// як добуток (k+1)(k+2)...(2k+2); це трактування зафіксовано в README.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;
int main(){
    long double eps; cout<<"Enter calculation accuracy (e.g. 1e-6): ";cin>>eps;
    if(eps<=0)return 1;
    long double total=0;
    cout<<setw(5)<<"x"<<setw(8)<<"k"<<setw(22)<<"term"<<setw(22)<<"sum\n";
    for(int x=1;x<=5;++x){
        long double inner=0, term=1.0L/x;
        for(int k=0;k<10000;++k){
            if(k==0) term=1.0L/x;
            else {
                // t_k / t_(k-1) = -x * D_(k-1)/D_k.
                // D_k = product(j=k+1..2k+2) j.
                long double ratio=1.0L;
                for(int j=k+1;j<=2*k+2;++j) ratio/=j;
                for(int j=k;j<=2*k;++j) ratio*=j;
                term *= -x*ratio;
            }
            if(!isfinite((double)term)||fabsl(term)>1e38L|| (term!=0&&fabsl(term)<1e-38L))break;
            inner+=term;
            cout<<setw(5)<<x<<setw(8)<<k<<setw(22)<<setprecision(10)<<(double)term<<setw(22)<<(double)inner<<'\n';
            if(k>0&&fabsl(term)<eps)break;
        }
        total+=inner;
    }
    cout<<"Double sum = "<<(double)total<<'\n';
}

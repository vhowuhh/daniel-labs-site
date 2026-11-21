// Лабораторна робота №4, варіант 9, завдання 1: ln(x) у ряд Тейлора.
// Ряд ln(x)=sum((-1)^(n+1)*(x-1)^n/n), збігається для 0<x<2;
// точка x=2 також має умовну збіжність.
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double taylorLn(double x,double eps){
    double z=x-1, term=z, sum=0;
    for(int n=1;n<1000000;++n){
        double add=(n%2?1.0:-1.0)*term/n;
        sum+=add;
        if(fabs(add)<eps)break;
        term*=z;
    }
    return sum;
}
int main(){
    double a,b,h,eps;
    cout<<"Enter x_min, x_max, step: ";cin>>a>>b>>h;
    cout<<"Enter accuracy from 1e-2 to 1e-6: ";cin>>eps;
    if(h<=0||a>b||eps<1e-6||eps>1e-2)return 1;
    cout<<setw(12)<<"x"<<setw(18)<<"Taylor ln(x)"<<setw(18)<<"std ln(x)"<<setw(18)<<"error\n";
    for(double x=a;x<=b+1e-12;x+=h){
        if(x<=0||x>2){cout<<setw(12)<<x<<" function is not defined by this series\n";continue;}
        double approx=taylorLn(x,eps), exact=log(x);
        cout<<setw(12)<<x<<setw(18)<<approx<<setw(18)<<exact<<setw(18)<<fabs(approx-exact)<<'\n';
    }
}

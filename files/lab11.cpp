// Лабораторна робота №11, варіант 9
// 9.1: статистика чисел і слів у кожному рядку текстового файла.
// 9.2: бінарний файл товарних пропозицій з додаванням, заміною, видаленням і запитами.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
using namespace std;
struct Offer { char company[60]; char product[60]; double price; int deliveryDays; };
void taskText(){
    string inName="input_text.txt", outName="text_report.txt";
    ofstream in(inName); if(!in){cout<<"Cannot create input file\n";return;}
    cout<<"Enter text lines (a single # ends input):\n"; string line;
    while(getline(cin,line)&&line!="#") in<<line<<'\n'; in.close();
    ifstream src(inName); ofstream dst(outName); int lineNo=0;
    while(getline(src,line)){ ++lineNo; istringstream ss(line); string token; int positive=0,negative=0,zero=0,words=0;
        while(ss>>token){ char* end=nullptr; double value=strtod(token.c_str(),&end); if(end!=token.c_str()&&*end=='\0'){ if(value>0)++positive; else if(value<0)++negative; else ++zero; } else ++words; }
        dst<<"Line "<<lineNo<<": positive numbers="<<positive<<", negative numbers="<<negative<<", zero numbers="<<zero<<", words="<<words<<'\n';
    }
    cout<<"Report saved to "<<outName<<'\n';
}
void readOffer(Offer& x){ string s; cout<<"Company: ";cin.ignore();getline(cin,s);snprintf(x.company,sizeof(x.company),"%s",s.c_str()); cout<<"Product: ";getline(cin,s);snprintf(x.product,sizeof(x.product),"%s",s.c_str()); cout<<"Price and delivery days: ";cin>>x.price>>x.deliveryDays; }
vector<Offer> load(){ vector<Offer> a; ifstream f("offers.dat",ios::binary); Offer x; while(f.read((char*)&x,sizeof x))a.push_back(x); return a; }
void save(const vector<Offer>& a){ ofstream f("offers.dat",ios::binary|ios::trunc); for(auto& x:a)f.write((char*)&x,sizeof x); }
void show(const vector<Offer>& a){ cout<<left<<setw(22)<<"Company"<<setw(22)<<"Product"<<setw(12)<<"Price"<<"Days\n"; for(auto&x:a)cout<<left<<setw(22)<<x.company<<setw(22)<<x.product<<setw(12)<<x.price<<x.deliveryDays<<'\n'; }
void taskBinary(){
    vector<Offer> a=load(); if(a.empty()){cout<<"No records yet. Enter initial number of offers: ";int n;cin>>n;for(int i=0;i<n;++i){Offer x;readOffer(x);a.push_back(x);}save(a);}
    int cmd; do{cout<<"\n1 Show  2 Add  3 Replace  4 Delete  5 Supplier within 2 days for product  6 Products by company under price  7 Sort by delivery  0 Exit\nChoice: ";cin>>cmd;
        if(cmd==1)show(load());
        else if(cmd==2){Offer x;readOffer(x);a=load();a.push_back(x);save(a);}
        else if(cmd==3||cmd==4){a=load();show(a);int i;cout<<"Record number (1.."<<a.size()<<"): ";cin>>i;if(i<1||i>(int)a.size())continue;if(cmd==3){Offer x;readOffer(x);a[i-1]=x;}else a.erase(a.begin()+i-1);save(a);}
        else if(cmd==5){a=load();string p;cout<<"Product name: ";cin.ignore();getline(cin,p);for(auto&x:a)if(x.product==p&&x.deliveryDays<=2)cout<<x.company<<" - "<<x.deliveryDays<<" days\n";}
        else if(cmd==6){a=load();string c;double maxPrice;cout<<"Company: ";cin.ignore();getline(cin,c);cout<<"Maximum price: ";cin>>maxPrice;for(auto&x:a)if(c==x.company&&x.price<=maxPrice)cout<<x.product<<" - "<<x.price<<'\n';}
        else if(cmd==7){a=load();stable_sort(a.begin(),a.end(),[](const Offer&x,const Offer&y){return x.deliveryDays<y.deliveryDays;});save(a);show(a);}
    }while(cmd!=0);
}
int main(){cout<<"Task 9.1\n";taskText();cout<<"\nTask 9.2\n";taskBinary();}

#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
using namespace std;

// ЛР №10, варіант 29 -> варіант 4 (25 варіантів).
// Структура: факультет, курс, група, прізвище студента, екзаменаційні оцінки.
const int MAX_STUDENTS=100, MAX_NAME=40, SUBJECTS=5;
struct Student { char faculty[MAX_NAME], group[MAX_NAME], surname[MAX_NAME]; int course; int grades[SUBJECTS]; };
void readLine(char* dst,int size,const char* prompt){cout<<prompt;cin>>ws;cin.getline(dst,size);}
void printHeader(){cout<<left<<setw(15)<<"Факультет"<<setw(7)<<"Курс"<<setw(12)<<"Група"<<setw(18)<<"Прізвище"<<"Оцінки\n";cout<<string(75,'-')<<'\n';}
void printStudent(const Student& s){cout<<left<<setw(15)<<s.faculty<<setw(7)<<s.course<<setw(12)<<s.group<<setw(18)<<s.surname;for(int g:s.grades)cout<<g<<' ';cout<<'\n';}
void printAll(const Student a[],int n){if(!n){cout<<"Масив порожній.\n";return;}printHeader();for(int i=0;i<n;i++)printStudent(a[i]);}
void input(Student a[],int& n){cout<<"Кількість студентів (1.."<<MAX_STUDENTS<<"): ";cin>>n;if(!cin||n<1||n>MAX_STUDENTS){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');n=0;cout<<"Некоректна кількість.\n";return;}
 for(int i=0;i<n;i++){cout<<"\nСтудент №"<<i+1<<"\n";readLine(a[i].faculty,MAX_NAME,"Факультет: ");cout<<"Курс: ";cin>>a[i].course;readLine(a[i].group,MAX_NAME,"Група: ");readLine(a[i].surname,MAX_NAME,"Прізвище: ");cout<<"Введіть "<<SUBJECTS<<" оцінок (1..5): ";for(int j=0;j<SUBJECTS;j++){cin>>a[i].grades[j];if(a[i].grades[j]<1||a[i].grades[j]>5)a[i].grades[j]=3;}}
 cout<<"\nВведений масив:\n";printAll(a,n);
}
void queryAverage(Student a[],int n){if(!n){cout<<"Спочатку введіть дані.\n";return;}cout<<"Факультет для пошуку: ";char faculty[MAX_NAME];cin>>ws;cin.getline(faculty,MAX_NAME);bool found=false;cout<<"Факультет і курс, на якому середній бал не менше 3.5:\n";
 for(int i=0;i<n;i++)if(strcmp(a[i].faculty,faculty)==0){double sum=0;for(int g:a[i].grades)sum+=g;if(sum/SUBJECTS>=3.5){if(!found)printHeader();printStudent(a[i]);found=true;}}if(!found)cout<<"Відповідних записів не знайдено.\n";
}
void excellentOnly(Student a[],int n){if(!n){cout<<"Спочатку введіть дані.\n";return;}bool found=false;cout<<"Студенти, які не мають трійок і двійок (усі оцінки 4 або 5):\n";for(int i=0;i<n;i++){bool ok=true;for(int g:a[i].grades)if(g<4)ok=false;if(ok){if(!found)printHeader();printStudent(a[i]);found=true;}}if(!found)cout<<"Відповідних студентів не знайдено.\n";
}
void bestGroup(Student a[],int n){if(!n){cout<<"Спочатку введіть дані.\n";return;}char bestFaculty[MAX_NAME]="",bestGroupName[MAX_NAME]="";int best=-1;
 for(int i=0;i<n;i++){int count=0;for(int j=0;j<n;j++)if(strcmp(a[i].faculty,a[j].faculty)==0&&strcmp(a[i].group,a[j].group)==0){bool excellent=true;for(int g:a[j].grades)if(g!=5)excellent=false;if(excellent)count++;}if(count>best){best=count;strcpy(bestFaculty,a[i].faculty);strcpy(bestGroupName,a[i].group);}}
 cout<<"Факультет і група з найбільшою кількістю відмінників: "<<bestFaculty<<", група "<<bestGroupName<<".\nКількість відмінників: "<<best<<"\n";
}
int main(){Student students[MAX_STUDENTS];int n=0,choice;do{cout<<"\n=== Лабораторна робота №10 ===\n1. Ввести масив структур\n2. Вивести масив структур\n3. Факультет і курс із середнім балом не менше 3.5\n4. Студенти без оцінок 2 і 3\n5. Факультет і група з найбільшою кількістю відмінників\n0. Вихід\nВаш вибір: ";cin>>choice;switch(choice){case 1:input(students,n);break;case 2:printAll(students,n);break;case 3:queryAverage(students,n);break;case 4:excellentOnly(students,n);break;case 5:bestGroup(students,n);break;case 0:break;default:cout<<"Невірний пункт меню.\n";}}while(choice!=0);return 0;}

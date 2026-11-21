// Лабораторна робота №9, варіант 9
// Обробка рядків без використання string-алгоритмів STL у завданні 9.1.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cctype>
using namespace std;
bool isDelimiter(char c){ return isspace((unsigned char)c)||c==','||c=='.'||c==';'||c==':'||c=='!'||c=='?'||c=='('||c==')'; }
int main(){
    cout << "Enter a line: "; string line; getline(cin,line);
    if(line.empty()) getline(cin,line);
    vector<string> words; for(size_t i=0;i<line.size();){ while(i<line.size()&&isDelimiter(line[i]))++i; size_t j=i; while(j<line.size()&&!isDelimiter(line[j]))++j; if(j>i) words.push_back(line.substr(i,j-i)); i=j; }
    map<string,int> counts; for(auto w:words){ string key=w; for(char& c:key)c=(char)tolower((unsigned char)c); ++counts[key]; }
    cout << "Repeated words:\n"; for(auto [w,c]:counts) if(c>1) cout<<w<<" - "<<c<<" times\n";
    set<string> seen; string uniqueLine;
    for(const string& w:words){ string key=w; for(char& c:key)c=(char)tolower((unsigned char)c); if(seen.insert(key).second){ if(!uniqueLine.empty())uniqueLine+=' '; uniqueLine+=w; } }
    cout << "After removing duplicates: " << uniqueLine << '\n';
    for(size_t i=0;i<line.size();++i){ bool inside=(i>0&&!isDelimiter(line[i-1]))&&(i+1<line.size()&&!isDelimiter(line[i+1])); if(inside&&isupper((unsigned char)line[i])) line[i]=(char)tolower((unsigned char)line[i]); }
    cout << "Uppercase letters inside words changed to lowercase: " << line << '\n';
    cout << "\nTask 9.2: enter a C-like code fragment (one line):\n";
    string code; getline(cin,code); if(code.empty()) getline(cin,code);
    map<string,string> types; string token; stringstream ss(code);
    while(ss>>token){ if(token=="int"||token=="double"||token=="float"||token=="char"||token=="long") { string name; if(ss>>name){ while(!name.empty()&&!isalpha((unsigned char)name.back())&&!isdigit((unsigned char)name.back())&&name.back()!='_')name.pop_back(); if(!name.empty())types[name]=token; } } }
    cout << "Identifiers on right sides of assignments and their declared types:\n";
    set<string> printed;
    size_t p=0; while((p=code.find('=',p))!=string::npos){ if(p+1<code.size()&&code[p+1]=='='){p+=2;continue;} size_t end=code.find(';',p); if(end==string::npos)end=code.size(); string rhs=code.substr(p+1,end-p-1); for(auto [name,type]:types){ size_t q=rhs.find(name); if(q!=string::npos&&printed.insert(name).second)cout<<name<<" - "<<type<<'\n'; } p=end+1; }
}

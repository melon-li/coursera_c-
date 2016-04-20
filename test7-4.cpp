#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void process(string *p, int n, string cmd){
    
}

int main(){
    int n = 0;
    int i = 0;
    char buf[501];
    string tmp;
    string *p;

    cin>>n;
    p = new string [n];
    while(i<n){
        cin>>*(p + i);   
        i++;
    }    
 
    while(true){
        cin.getline(buf, 500);
        tmp = buf; 
        if(tmp.empty())continue;
        if(tmp.find("over") == 0 && tmp.length() == strlen("over")) break;
        process(p, n, tmp);
    }
}

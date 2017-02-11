#include <iostream>
#include <cstring>
#include <stdint.h>
using namespace std;
class Base{
    public:
        ~Base(){cout<<"Byte from Base"<<endl;}
};

class He:public Base{
    public:
        ~He(){cout<<"Byte from He"<<endl;}
};

int main(){
    He *p = new He;
    delete p;
    enum color{red, blue};
    color r = red;
    string c[2]={"red", "blue"};
    cout<<c[r]<<endl;
    char r2[5]="abcd";
    r2[3]='\0';
    cout<<strlen(r2)<<endl;
    return 0;
}

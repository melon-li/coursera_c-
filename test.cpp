#include <iostream>
#include <cstring>
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
    return 0;
}

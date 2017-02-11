#include <iostream>
using namespace std;
class A {
public:
    int val;
    A():val(0){}
    A(int v){
        val = v;
      //  cout<<"Type switch construct val="<<val<<endl;
    }
    A(const A& a){ 
        val = a.val;
     //   cout<<"Copy construct val="<<val<<endl;
    }
    ~A(){
     //   cout<<"Destruct val="<<val<<endl;
    }
    A&  GetObj(){
        A & a = *this;
        return a;
      //  return *this;
    }
};
main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
}

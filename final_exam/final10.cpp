#include <iostream>
#include <map>
using namespace std;

class A{
    public:
        static int count;
        int n;
        A():n(0){count++;}
        A(int n_):n(n_){count++;}
        A(const A &a){n=a.n;count++;}
        virtual  ~A(){count--;cout<<"A::destructor"<<endl;}
};
int A::count = 0;


class B: public A{
    public:
        B():A(){}
        B(int n_):A(n_){}
        B(const B &b):A(b){}
        virtual ~B(){cout<<"B::desctructor"<<endl;}
};

void func(B b) { }
int main()
{
        A a1(5),a2;
        cout << A::count << endl;
        B b1(4);
        cout << A::count << endl;
        func(b1);
        cout << A::count << endl;
        A * pa = new B(4);
        cout << A::count << endl;
        delete pa;
        cout << A::count << endl;
        return 0;
}

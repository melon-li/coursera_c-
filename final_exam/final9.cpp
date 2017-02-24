#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A{
    public:
        char sex;
        int age;
        A(int k):age(k){sex = 'A';}
        bool operator<(const A &a){
            return age < a.age;
        }
};

class B:public A{
    public:
        B(int k):A(k){sex = 'B';}
};

class Comp{
    public:
        bool operator()(A *a1, A *a2){
            return *a1 < *a2;
        }
};

void Print(A *a){
    cout<<a->sex<<" "<<a->age<<endl;
}

int main()
{
        int t;
        cin >> t;
        set<A*,Comp> ct;
        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i)  {
                        char c; int k;
                        cin >> c >> k;

                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }
}

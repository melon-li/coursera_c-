#include<iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n=0): num(n) {}
    Number operator* (const Number &n1){
        Number n2;
        n2.num = n1.num*num;
        return n2;
    }
//  重载类型转换方程，不能有返回值
    operator int(){
        return num;
    }
};

int main() {
    Number n1(10), n2(20);
    Number n3;n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}

#include <iostream>
using namespace std;
class Complex{
    public:
        double real;
        double image;
        Complex(int i){
            cout << "IntConstructor called" <<endl;
            real = i;
            image = 0;
        }
        
       Complex(double r, double i){
           real = r;
           image = i;
       }
};

int main(){
    Complex c1(7, 8);
    Complex c2 = 12;
    c1 = 9;
    cout << c1.real << "," << c1.image <<endl;
    return 0;
}

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:    
    double r,i;
public:    
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    Complex & operator=(string s){
        string r_s = "";
        string i_s = "";
        double r_val = 0;
        double i_val = 0;
        //cout << s << endl;
        int pos = s.find('+', 0);
        //cout << pos << endl;
        // if there are a real part and  an imaginary part
        if(pos>0){
            int pos2 = s.find('i', 0);
            //cout << "pos2:" << pos2<<endl;
            if(pos < pos2){
                r_s = s.substr(0, pos);
                //cout << s.substr(0, pos);
                i_s = s.substr(pos+1,pos2-pos-1);
            }else{
                r_s = s.substr(pos+1,s.length());
                i_s = s.substr(0, pos2);
            }
            //cout<<"i_s:"<<i_s.c_str()<<endl;
            //cout <<"r i:"<< r_s<<endl;
            if(i_s == "") i_s = "1";
            r_val = atof(r_s.c_str());
            i_val = atof(i_s.c_str());
        //there is a real part or an imaginary part
        }else{
            pos = s.find('i',0);
            if(pos>0){
                
                i_val = atof(s.substr(0, pos).c_str());
            }else{
                r_val = atof(s.c_str());
            }
        }
        r = r_val;
        i = i_val;
        return *this;
    }
};
int main() {
    Complex a;
    a = "40+10i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}

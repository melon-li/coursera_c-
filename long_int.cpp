# include <iostream>
# include <cstring>
#include <cstdlib>
 
using namespace std;

class LongInt{
    private:
        int size;
        int *p;
    public:
        LongInt(){size=0;p=NULL;}
        LongInt(const char *sp);
        LongInt & operator=(string s);
        LongInt & operator+(const LongInt & b);
        friend ostream & operator<<(ostream & o, const LongInt &li);
        friend istream &  operator>>(istream & i, LongInt & li);
        

};

LongInt::LongInt(const char *sp){
    string s = sp;
    operator=(s);
}

ostream & operator<<(ostream & o, const LongInt &li){
    for(int i=0; i< li.size; i++){
        o<<li.p[i];
    }
    return o;
}

LongInt & LongInt::operator=(string s){
    string str;
    int len = s.length();
    int num = len/10 + 1;
    size = num;
    p = new int[num];
    int cnt = 0;
    while(len > 10){
         str = s.substr(0, 10);
         p[cnt++] = atoll(str.c_str());
         len = len - 10;
         s = s.substr(10, len);
    }
    str = s.substr(0, len);        
    p[cnt] = atoll(str.c_str());
    return *this;
    
}

LongInt & LongInt::operator + (const LongInt & b){
    int max;
    int tmp, tmp1, tmp2;
    string str;
    long high = 0;
    if(size > b.size){
        max = b.size;
    }else{
        max = size;
    }
    for(int i=0; i< max; i++){
        if(i>(size-1)){
            tmp1 = 0;
        }else{
            tmp1 = p[i];
        }
        if(i>(b.size-1)){
            tmp2 = 0;
        }else{
            tmp2 = b.p[i];
        }

        cout << "tmp:" << tmp1 << tmp2;
        tmp = tmp1 + tmp2 + high;
        cout << "tmp:"<< tmp<<endl;
        str = itoa(tmp); 
        cout << "str:" << str<<endl;
        if(str.length() > 9){
            high = atoll(str.substr(9, str.length() - 9).c_str());
            p[i] = atoll(str.substr(0, 9).c_str());        
        }else{
            high = 0;
            p[i] = atoll(str.substr(0, str.length()).c_str());        
        }
    }
    return *this;
}

istream &  operator>>(istream & i, LongInt & li){
    string s;
    i>>s;
    li = s;
    return i;
}

int main(){
    LongInt li1;
    LongInt li2;
    LongInt li3;
    cin >> li1;
    cin >> li2;
    li3 = li1 + li2; 
    cout<< li1 <<endl;
}

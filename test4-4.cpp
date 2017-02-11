#include <iostream>
#include <cstring>
#include <stdint.h>
#include <stdio.h>

using namespace std;
const uint32_t MAX_L=201;

class Bign{
    private:
        char *n;
        uint32_t len;
        bool flag;

    public:
        Bign(){n=NULL; len=0; flag=0;}
        Bign(const Bign &n);
        Bign(char *str);
        Bign(char *str, int);
        Bign(int32_t i);
        ~Bign(){if(n) delete [] n;}
 
        uint32_t length(){return len;}

        friend ostream & operator<<(ostream &o, const Bign &b);
        friend istream & operator>>(istream &i, Bign &b);

        Bign & operator=(const int32_t i);
        Bign & operator=(const char *str);
        Bign & operator=(const Bign& b);
        bool operator==(const Bign &b);
        bool operator>(const Bign &b);
        bool operator<(const Bign &b);
        bool operator<=(const Bign &b);

        Bign operator+(const Bign & b);
        Bign operator-(const Bign & b);
        Bign operator*(const Bign & b);
        Bign operator*(const int32_t i);
        Bign operator/(const Bign & b);

        Bign abs(Bign b){ b.flag = 0; return b;}
};

Bign::Bign(const Bign &b){
    n = NULL;
    len = 0;
    flag = 0;
    if(b.n){
        n = new char[b.len];
        memcpy(n, b.n, b.len);
        len = b.len;
        flag = b.flag;
    }
}

Bign::Bign(char *str){
    n = NULL;
    len = 0;
    flag = 0;
    if(str){
        uint8_t start = 0;
        flag = 0;
        if(str[0] == '+'){start=1; flag=0;}
        if(str[0] == '-'){start=1; flag=1;}
        len = strlen(str) - start;
        n = new char[len];
        for(uint32_t i=0; i<len; i++)
            n[len-1-i] = str[i+start];
    }
}

Bign::Bign(char *str, int){
    n = NULL;
    len = 0;
    flag = 0;
    if(str){
        uint8_t start = 0;
        flag = 0;
        if(str[0] == '+'){start=1; flag=0;}
        if(str[0] == '-'){start=1; flag=1;}
        len = strlen(str) - start;
        n = new char[len];
        memcpy(n, str+start, len);
    }
}

Bign::Bign(int32_t i){
    n = NULL;
    len = 0;
    flag = 0;
    *this = i;
}

ostream &operator<<(ostream &o, const Bign &b){
    if(b.flag) o<<'-';
    for(int32_t i=b.len-1; i>=0; i--) o<<b.n[i];
    return o;
}

istream &operator>>(istream &i, Bign &b){
    string str;
    i>>str;
    uint8_t start = 0;
    b.flag = 0;
    if(str[0] == '+'){start=1; b.flag=0;}
    if(str[0] == '-'){start=1; b.flag=1;}
    b.len = str.length() - start;
    b.n = new char[b.len];
    const char *tmp = str.c_str() + start;
    for(int32_t j=0; j<b.len; j++)
        b.n[b.len-1-j] = tmp[j];
    return i;
}
 
Bign& Bign::operator=(const int32_t i){
    char l = 30;
    char s[l];
    memset(s, '\0', l);
    sprintf(s, "%d", i);
    *this = s;
    return *this;       
}

Bign& Bign::operator=(const char *str){
    char *t;
    if(str){
        uint8_t start = 0;
        flag = 0;
        if(str[0] == '+'){start=1; flag=0;}
        if(str[0] == '-'){start=1; flag=1;}
        len = strlen(str) - start;
        t = new char[len];
        for(uint32_t i=0; i<len; i++)
            t[len-1-i] = str[i+start];
        if(n)delete [] n;
        n = t;
    }else{
        if(n)delete [] n;
        n = NULL;
        len = 0;
        flag = 0;
    }
    return *this;   
}

Bign& Bign::operator=(const Bign& b){
    if(!b.n) return *this;
    flag = b.flag;
    len = b.len;
    char *t = new char[len];
    memcpy(t, b.n, len);
    if(n) delete []n;
    n = t;
    return *this;
}

bool Bign::operator==(const Bign &b){
    if(flag != b.flag) return false;
    if(len != b.len) return false;
    for(uint32_t i = 0; i<len; i++){
        if(n[i] != b.n[i]) return false;
    }
    return true;
}

bool Bign::operator>(const Bign &b){
    if(flag < b.flag) return true;
    if(flag > b.flag) return false;
    if(len < b.len) return flag;
    if(len > b.len) return !flag;
    for(int32_t i=len-1; i>=0; i--){
        if(n[i] > b.n[i]) return !flag;
        if(n[i] < b.n[i]) return flag;
    }
    return false;
}

bool Bign::operator<(const Bign &b){
    if(flag > b.flag) return true;
    if(flag < b.flag) return false;
    if(len > b.len) return flag;
    if(len < b.len) return !flag;
    for(int32_t i=len-1; i>=0; i--){
        if(n[i] < b.n[i]) return !flag;
        if(n[i] > b.n[i]) return flag;
    }
    return false;
}

bool Bign::operator<=(const Bign &b){
    return !(*this > b);
}

Bign  Bign::operator+(const Bign & b){
    if(!b.n) return *this;
    if(!n) return b;
    if(flag == b.flag){
        char ext = 0;
        int32_t i = 0;
        uint32_t l = len > b.len ? len: b.len;
        char r[l+2];
        char x1, x2, y;
        for(i=0; i<l; i++){
           x1 = i < len ? n[i]: '0'; 
           x2 = i < b.len ? b.n[i]: '0';
           y = (x1 - '0') + (x2 - '0') + ext;
           r[i] = y%10 + '0';
           ext = y/10;
        }
        if(ext) r[i++] = ext + '0';
        r[i] = '\0';
        return Bign(r, 0);
    }
    Bign abs1 = abs(*this);
    Bign abs2 = abs(b);
    bool f = abs1 > abs2 ? flag : !flag;
    Bign v = abs1 - abs2;
    v.flag = f;
    return v;
}

Bign Bign::operator-(const Bign &b){
    if(!b.n) return *this;
    if(!n){
        Bign r = Bign(b);
        r.flag = !r.flag;
        return r;
    }

    Bign abs1 = abs(*this);
    Bign abs2 = abs(b);
    bool f =  abs1 > abs2 ? flag: !flag;
    Bign max = abs1 < abs2 ? abs2: abs1;
    Bign min = abs1 < abs2 ? abs1: abs2;
    uint32_t l = len > b.len ? len: b.len;
    uint32_t rl= l + 1;
    char r[rl];
    uint32_t i = 0;
    char x1 = 0, x2 = 0, y = 0;
    char borrow = 0;
    memset(r, '0', rl);
    if(flag == b.flag){
        for(i=0; i<l; i++){
            x1 = i < max.len ? max.n[i]:'0';
            x2 = i < min.len ? min.n[i]:'0';
            y = (x1-'0') -(x2-'0')-borrow;
            borrow = y < 0 ? 1: 0;
            y = y < 0 ? (y+10): y;
            r[i] = y + '0';
        }
        for(int32_t j=rl-1; j>=1; j--){ if(r[j] != '0'){ break;} r[j] = '\0';}
        Bign r3(r, 0);
        r3.flag = f;
        return r3;
    }

    Bign r2 = abs1 + abs2;
    r2.flag = flag;
    return r2;
    
}

Bign Bign::operator*(const Bign &b){
    uint32_t l = len + b.len+1;
    char r[l];
    int32_t i = 0;
    int32_t j = 0;
    memset(r, 0, l);
    for(i=0; i<len; i++){
        for(j=0; j<b.len; j++)
            r[i+j] = (n[i]-'0')*(b.n[j]-'0');
    }
    for(i=0; i<l; i++){
        r[i+1] += r[i]/10;
        r[i] = r[i]%10;
    }
    for(i=0; i<l; i++) r[i] += '0'; 
    for(i=l-1; i>=1; i--){ if(r[i] != '0')break; r[i]='\0';}
    Bign rc(r, 0);
    rc.flag = flag ^ b.flag;
    return rc;
}


Bign Bign::operator*(const int32_t i){
   Bign b = i;
   Bign t = *this; 
   return b*t;
}

Bign Bign::operator/(const Bign &b){
    if(len < b.len){
        Bign rc;
        rc = 0;
        if(flag ^ b.flag) rc = "-1"; 
        return rc;
    }

    int32_t tl = len - b.len + 1;
    char r[tl+1];
    char tmp[len];
    int32_t l = len -1;
    int32_t dbl = tl -1;
    int32_t i = 0;
    Bign divisor = *this;
    Bign divid = b;
    memset(r, '0', (tl+1)*sizeof(char));
    while(dbl>=0){
        l = divisor.len - 1;
        if(dbl > l) dbl = l;
        memset(tmp, '\0', len);
        for(i=l; i>=dbl; i--)
            tmp[l-i] = divisor.n[i];
        Bign dividor_t(tmp);
        if(dividor_t < divid){dbl--; continue;}
        int32_t key = 0;
        while(divid*key <= dividor_t) key++;
        key--;
        r[dbl] = key + '0';
        Bign t = divid*key;
        for(i=0; i<dbl; i++) t = t*10;
        divisor = divisor - t;
        dbl--;
    }
    for(int32_t i=tl; i>=1; i--){if(r[i] != '0') break;r[i]='\0';}
    Bign rc(r, 0);
    rc.flag = flag ^ b.flag;
    return rc;
}

int main(){
    Bign a, b, r;
    char op;
    cin >> a >> op >> b;
    switch (op) {
    case '+':
        r = a + b;
        break;
    case '-':
        r = a - b;
        break;
    case '*':
        r = a*b;
        break;
    case '/':
        r = a / b;
        break;
    default:
        break;
    }
    cout << r<<endl;
}

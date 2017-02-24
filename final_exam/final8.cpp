#include <iostream>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t-- > 0){
        int n, i, j, k;
        cin>>n>>i>>j;
        if(n < 0) return -1;
        if(i >= j-1) return -1;
        if(i < 0 || j >= 31) return -1;
        k = n ^ (1<<j);
        int t1 = 0;
        for(int x=0; x<j; x++) t1 |= 1<<x;
        int t2 = 0;
        for(int x=0; x<=i+1; x++) t2 |= 1<<x;
        int t = t1 ^ t2;
        k = k | t;
        t1 |= 1<<j;
        k = k & t1;
        t2 ^= 3<<i;
        k = k & (~t2);
        cout<<hex<<k<<endl;
    }
}

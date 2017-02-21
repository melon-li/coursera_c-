#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void print(stack<int> pq){
    while(!pq.empty()) {  
        cout << pq.top() << " ";
        pq.pop();
    }
}

void print(priority_queue< int, vector<int>, greater<int> > pq){
    while(!pq.empty()) {  
        cout << pq.top() << " ";
        pq.pop();
    }
}


bool isnum(string item){
    string nums="0123456789";
    int first = item.find_first_of(nums);
    if(first == string::npos) return false;
    return true;
}

template<int n>
class Test{
    public:
    int size;
    Test(){size = n;cout<<n<<endl;}
    void print();
};

template<int n>
void Test<n>::print(){
    cout<<"print n="<<n<<endl;
}
int main(int argc, char *argv[])
{

   string item;
   int i = 20;
   item = 20 + '0';
   cout<<"item="<<atoi("123")<<endl;
}

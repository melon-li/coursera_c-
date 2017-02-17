#include <iostream>
#include <queue>
using namespace std;

void print(priority_queue<int> pq){
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

int main(int argc, char *argv[])
{
        priority_queue <int> pq;
        //priority_queue< int, vector<int>, greater<int> > pq;
        pq.push(1);
        pq.push(2);
        pq.push(3);
        pq.push(9);
        print(pq);
        cout<<endl;
        print(pq);
        cout << endl;
                                                                return 0;
}

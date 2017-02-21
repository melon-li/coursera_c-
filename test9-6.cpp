#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int prime_descomposition(int n){
    int old = n;
    int cnt = 0;
    if( n < 2) return 0;
    for(int i=2; i<=sqrt(n); i++){
        while( i != n){
            if(n%i != 0) break;
            //cout<<i<<"*";
            cnt++;
            n = n/i;
        }
    }
    if(old == n) return 0;
    //cout<<n<<endl;
    cnt++;
    return cnt;
}

int main(){
    int time;
    int n;
    cin>>time;
    vector<int> v;
    pair<int, int> max_pair;
    pair<int, int> min_pair;
    priority_queue<pair<int, int> > pq;
    priority_queue<pair<int, int>, 
        vector<pair<int, int> >,
        greater<pair<int,int> > > pqg;

    while(time--){
        for(int i=0; i<10; i++)
        {
            cin>>n;
            v.push_back(n);
            pq.push(make_pair(prime_descomposition(n),n));
            pqg.push(make_pair(prime_descomposition(n),n));
        }
        max_pair = pq.top();
        min_pair = pqg.top();
        cout<<max_pair.second<<" "<<min_pair.second<<endl; 
    }
    return 0;
}

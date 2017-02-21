#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <queue>
#include <set>

using namespace std;


void split(const string &cmd, vector<string> & v){
    stringstream ss;
    ss.str(cmd);
    string item;
    while(getline(ss, item, ' ')){
        if(item == " ")continue;
        v.push_back(item);
    }
}


void process_cmd(const string &cmd, multiset<int> & s, set<int> &record){
    vector<string> v;
    split(cmd, v);
    string c = v[0];
    int e = atoi(v[1].c_str());
    if(c == "add"){
        s.insert(e);
        record.insert(e);
        cout<<s.count(e)<<endl;
    }else if(c == "del"){
        int cnt = s.erase(e);
        cout<<cnt<<endl;
    }else if(c == "ask"){
        set<int>::iterator it = record.find(e);
        if(it == record.end()){
            cout<<"0 0"<<endl;
        }else{
            int cnt = s.count(e);
            cout<<"1 "<<cnt<<endl;
        }
    }
}

int main(){
    int times;
    string cmd;
    multiset<int> s;
    set<int> record;
    cin>>times;
    cin.ignore(1);
    while(times-- > 0){
        getline(cin, cmd);
        process_cmd(cmd, s, record);
    }
    return 0;
}

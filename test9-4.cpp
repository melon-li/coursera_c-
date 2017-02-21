#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

string i2str(int i){
    stringstream ss;
    ss<<i;
    return  ss.str();
}

class StringCmd{
    private:
        string *data;
        int n;
    public:
        StringCmd(int n_){
            data = NULL;
            n = n_;
            data = new string[n];
        }
        ~StringCmd(){if(data)delete [] data;}
        friend istream & operator>>(istream &in, StringCmd & sc);
        friend ostream & operator<<(ostream &out, StringCmd & sc);
        void split(const string &cmd, stack<string> & q);
        bool isnum(string item);
        void copy(stack<string> &args);
        void add(stack<string> &args);
        void find(stack<string> &args);
        void rfind(stack<string> &args);
        void insert(stack<string> &args);
        void reset(stack<string> &args);
        void print(stack<string> &args);
        void printall(stack<string> &args);
        void process_data(const string & cmd);
};


istream & operator>>(istream &in, StringCmd & sc){
    for(uint32_t i=0; i<sc.n; i++)
        in>>sc.data[i];
    return in;
}


ostream & operator<<(ostream &out, StringCmd & sc){
    for(uint32_t i=0; i<sc.n; i++){
        out<<sc.data[i];
        if(i<(sc.n-1))out<<",";
    }
    return out;
}


void StringCmd::split(const string &cmd, stack<string> & q){
    stringstream ss;
    ss.str(cmd);
    string item;
    while(getline(ss, item, ' '))
        q.push(item);
}


bool StringCmd::isnum(string item){
    string nums="0123456789";
    string sub;
    int first;

    if(item.length() > 5) return false;
    for(int32_t i=0; i<item.length(); i++)
        sub=item[i];
        first = sub.find_first_of(nums);
        if(first == string::npos) return false;
    return true;
}


void StringCmd::copy(stack<string> &args){
    string arg[3];
    if(args.size() < 3){
        cerr<<"The cmd copy args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<3; i++){
        arg[i] = args.top();
        args.pop();
    }
    uint32_t N = atoi(arg[0].c_str()) - 1;
    uint32_t X = atoi(arg[1].c_str());
    uint32_t L = atoi(arg[2].c_str());
    string r = data[N].substr(X, L);
    args.push(r);
}


void StringCmd::add(stack<string> &args){
    string arg[2];
    if(args.size() < 2){
        cerr<<"The cmd add args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<2; i++){
        arg[i] = args.top();
        args.pop();
    }
    if(isnum(arg[0]) && isnum(arg[1])){ 
        int t = atoi(arg[0].c_str()) + atoi(arg[1].c_str());
        args.push(i2str(t));
    }else{
        args.push(arg[0] + arg[1]);
    }
}


void StringCmd::find(stack<string> &args){
    string arg[2];
    if(args.size() < 2){
        cerr<<"The cmd find args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<2; i++){
        arg[i] = args.top();
        args.pop();
    }
    int32_t N = atoi(arg[1].c_str()) - 1;
    int32_t pos = data[N].find(arg[0]);
    string item;
    if(pos == string::npos){
        item = i2str(arg[0].length());
        args.push(item);
    }else{
        args.push(i2str(pos));
    }
}


void StringCmd::rfind(stack<string> &args){
    string arg[2];
    if(args.size() < 2){
        cerr<<"The cmd rfind args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<2; i++){
        arg[i] = args.top();
        args.pop();
    }
    int32_t N = atoi(arg[1].c_str()) - 1;
    int32_t pos = data[N].rfind(arg[0]);
    string item;
    if(pos == string::npos){ 
        item = i2str(arg[0].length());
        args.push(item);
    }else{
        item = i2str(pos);
        args.push(item);
    }
    
}


void StringCmd::insert(stack<string> &args){
    string arg[3];
    if(args.size() < 3){
        cerr<<"The cmd insert args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<3; i++){
        arg[i] = args.top();
        args.pop();
    }
    string S = arg[0];
    int32_t N = atoi(arg[1].c_str()) - 1;
    int32_t X = atoi(arg[2].c_str());
    data[N].insert(X, S);
}


void StringCmd::reset(stack<string> &args){
    string arg[2];
    if(args.size() < 2){
        cerr<<"The cmd reset args is error"<<endl;
        return;
    }
    for(int32_t i=0; i<2; i++){
        arg[i] = args.top();
        args.pop();
    }
    string S = arg[0];
    int32_t N = atoi(arg[1].c_str()) - 1;
    data[N] = S;

}


void StringCmd::print(stack<string> &args){
    string arg;
    if(args.size() < 1){
        cerr<<"The cmd print args is error"<<endl;
        return;
    }
    arg = args.top();
    args.pop();
    int32_t N = atoi(arg.c_str()) - 1;
    cout<<data[N]<<endl;
}


void StringCmd::printall(stack<string> &args){
    for(uint32_t i=0; i<n; i++)
        cout<<data[i]<<endl;
}


void StringCmd::process_data(const string &cmd){
    stack<string> cmds;
    stack<string> args;
    split(cmd, cmds);
    while(!cmds.empty()){
        string item = cmds.top();
        if(item == "copy"){
            copy(args);
        }else if(
        item == "add"){
            add(args);
        }else if(
        item == "find"){
            find(args);
        }else if(
        item == "rfind"){
            rfind(args);
        }else if(
        item == "insert"){
            insert(args);
        }else if(
        item == "reset"){
            reset(args);
        }else if(
        item == "print"){
            print(args);
        }else if(
        item == "printall"){
            printall(args);
        }else{
            args.push(item);
        }
        cmds.pop();
    }
    
}


int main(){
    int size;
    string cmd;

    cin>>size;
    StringCmd sc(size);
    cin>>sc;

    cin.ignore(1);
    getline(cin,cmd);
    while(cmd != "over"){
        sc.process_data(cmd);
        getline(cin, cmd);
    }
    return true;;

}

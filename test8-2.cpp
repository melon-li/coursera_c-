#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <queue>

using namespace std;

template <class T>
class ListId:public list<T>{
    public:
        int id;
        ListId *next;
        ListId(int id_): id(id_){next = NULL;}
};

template <class T>
class ListQue{
    private:
        ListId<T> *lip;
    public:
        ListQue(){lip = NULL;}
        ~ListQue(){
            ListId<T> *t = lip;
            while(t){
                lip = t;
                delete t;
                t = lip->next;
            }
        }
        ListId<T> & get_ListId(int id);
        void process_cmd(const string &cmd);
        void split(const string &cmd, vector<string> & q);
        void create(int id);
        void add(int id, T t);
        void merge(int id1, int id2);
        void unique(int id);
        void out(int id);

};


template <class T>
ListId<T> & ListQue<T>::get_ListId(int id){
    for(ListId<T> *i=lip; i!=NULL; i=i->next)
        if(i->id == id) return *i;
    return *lip;
}

template <class T>
void ListQue<T>::create(int id){
    ListId<T> *t = new ListId<T>(id);
    if(lip == NULL){
        lip = t;
    }else{
        lip->next = t;
    }
}

template <class T>
void ListQue<T>::add(int id, T t){
    ListId<T> & li = get_ListId(id);
    if(li.id != id) return;
    li.push_back(t);
}

template <class T>
void ListQue<T>::merge(int id1, int id2){
    ListId<T> & li1 = get_ListId(id1);
    ListId<T> & li2 = get_ListId(id2);
    if(li1.id != id1 || li2.id != id2) return;
    li1.merge(li2);
    li2.clear();
}

template <class T>
void ListQue<T>::unique(int id){
    ListId<T> & li = get_ListId(id);
    if(li.id != id) return;
    li.sort();
    li.unique();
}

template <class T>
void ListQue<T>::out(int id){
    ListId<T> & li = get_ListId(id);
    if(li.id != id) return;
    typename ListId<T>::iterator first = li.begin();
    typename ListId<T>::iterator last = li.end();
    for(;first != last; ++first)
        cout<<*first<<" ";
    cout<<endl;
}


template <class T>
void ListQue<T>::split(const string &cmd, vector<string> & v){
    stringstream ss;
    ss.str(cmd);
    string item;
    while(getline(ss, item, ' ')){
        if(item == " ")continue;
        v.push_back(item);
    }
}


template <class T>
void ListQue<T>::process_cmd(const string &cmd){
    vector<string> v;
    split(cmd, v);
    string c = v[0];
    if(c == "new"){
        create(atoi(v[1].c_str()));
    }else if(c == "add"){
        add(atoi(v[1].c_str()),
            atoi(v[2].c_str()));
    }else if(c == "merge"){
        merge(atoi(v[1].c_str()),
            atoi(v[2].c_str()));
    }else if(c == "unique"){
        unique(atoi(v[1].c_str()));
    }else if(c == "out"){
        out(atoi(v[1].c_str()));
    }
}

int main(){
    int times;
    string cmd;
    ListQue<int> lq;
    cin>>times;
    cin.ignore(1);
    while(times-- > 0){
        getline(cin, cmd);
        lq.process_cmd(cmd);
    }
    return 0;
}

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
using namespace std;
class Student{
private:
    char *name;
    char *id;
    uint32_t old;
    uint32_t *scores;
    uint32_t len;


public:
    Student(char *_name, char *_id, uint32_t _old){
        name = new char[strlen(_name)];
        strcpy(name, _name);
        id = new char[strlen(_id)];
        strcpy(id, _id);
        old = _old;
        scores = NULL;
        len = 0;
     }

    Student(char *str){
         char *s = strtok(str, ",");  
         name = new char[strlen(s)];
         strcpy(name, s);
         s = strtok(NULL, ",");

         old = atoi(s);
         s = strtok(NULL, ",");

         id = new char[strlen(s)];
         strcpy(id, s);
         s = strtok(NULL, ",");

         len = 0;
//         cout<<id<<endl;
//         name = id = NULL;
//         scores = NULL;
//         return;

         scores = new uint32_t[4];  

         uint32_t *t = NULL;
         while(s)  
         {  
             scores[len] = atoi(s);  
             //cout<<scores[len]<<endl;
             s = strtok(NULL, ",");  
             len++;  
             if(len%4 == 0 && s){
                 t = new uint32_t[(len/4+1)*4];
                 memcpy(t, scores, len);
                 delete [] scores; 
                 scores = t;
             }
         }  
    }

    ~Student(){
       if(name) delete [] name;
       if(id) delete [] id;
       if(scores) delete [] scores;
    }

   void set_scores(uint32_t *_scores, uint32_t len){
       scores = new uint32_t[len];
       memcpy(scores, _scores, sizeof(_scores));
   }

   void print_info(){
       uint32_t avg = 0;
       for(uint32_t i=0; i<len;i++){
           avg += scores[i];
       }
       cout<<name<<","<<old<<","<<id<<","<<(avg/len)<<endl;
   }
};


int main(int argc, char * argv[]){
    char str[100];
    cin>>str;
    Student s(str);
    s.print_info();
}

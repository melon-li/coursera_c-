#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

#define WARRIOR_NUM 5
#define HEADQUARTER_NUM 2
#define WEAPON_NUM 3

class Headquarter;
class Warrior{
    private:
        int number;
        int name_index;
        int life_val;
        int force_val;
        Headquarter *hq;
    
    public:
        static string names[WARRIOR_NUM];
        static string weapon_names[WEAPON_NUM]; 
        static char life_vals[WARRIOR_NUM];
        Warrior(Headquarter *hq, int num, int lv, int fv);
        virtual void print_result(int time);
};

class Headquarter{
    private:
        char stopped;
        int total_life_val;
        int total_warrior_val;
        Warrior * pwarrior[1000];
        
    public:
        char color; // 0 stands for red headquarter, 1 means blue
        char cur_index; // it is the index in producing_order array (WARRIOR_NUM) 
        static char producing_order[HEADQUARTER_NUM][WARRIOR_NUM];
        int warrior_num[WARRIOR_NUM];
        friend class Warrior;
        friend class Dragon;
        friend class Lion;
        char produce(int time);
        string get_color();
        void set_total_life(int tl);
        Headquarter(char c);
        ~Headquarter();
};

class Dragon:public Warrior{
    private:
        float morale;
        char weapons_index;
    public:
        Dragon(Headquarter *hq, int num, int lv, int fv);
        virtual void print_result(int time);
};


class Ninja:public Warrior{
    private:
        char weapons_index[2];
    public:
        Ninja(Headquarter *hq, int num, int lv, int fv);
        virtual void print_result(int time);
};

class Iceman:public Warrior{
    private:
        char weapons_index;
    public:
        Iceman(Headquarter *hq, int num, int lv, int fv);
        virtual void print_result(int time);
};


class Lion:public Warrior{
    private:
        int loyalty_index;
    public:
        Lion(Headquarter *hq, int num, int lv, int fv);
        virtual void print_result(int time);
};


Dragon::Dragon(Headquarter *hq, int num, int lv, int fv):Warrior(hq, num, lv, fv){
    morale = float(hq->total_life_val)/float(lv);
    weapons_index = num%3; 
}

void Dragon::print_result(int time){
    Warrior::print_result(time);
    printf("It has a %s, and it's morale is %.2f\n", Warrior::weapon_names[weapons_index].c_str(),morale);
}


Ninja::Ninja(Headquarter *hq, int num, int lv, int fv):Warrior(hq, num, lv, fv){
    weapons_index[0] = num%3; 
    weapons_index[1] = (num+1)%3; 
}

void Ninja::print_result(int time){
    Warrior::print_result(time);
    printf("It has a %s, and a %s\n", Warrior::weapon_names[weapons_index[0]].c_str(),
                                     Warrior::weapon_names[weapons_index[1]].c_str());
}


Iceman::Iceman(Headquarter *hq, int num, int lv, int fv):Warrior(hq, num, lv, fv){
    weapons_index = num%3; 
}

void Iceman::print_result(int time){
    Warrior::print_result(time);
    printf("It has a %s\n", Warrior::weapon_names[weapons_index].c_str());
}


Lion::Lion(Headquarter *hq, int num, int lv, int fv):Warrior(hq, num, lv, fv){
    loyalty_index = hq->total_life_val; 
}

void Lion::print_result(int time){
    Warrior::print_result(time);
    printf("It's logalty is  %d\n", loyalty_index);
}

Warrior::Warrior(Headquarter *hq, int num, int lv, int fv){
    this->hq = hq;
    this->number = num;
    this->life_val = lv;
    this->force_val = fv;
}

void Warrior::print_result(int time){
    string color_str = hq->get_color();
    char index = hq->producing_order[hq->color][hq->cur_index];
    printf("%03d %s %s %d born with strength %d, %d %s in %s headquarter\n",
            time, color_str.c_str(), names[index].c_str(), hq->total_warrior_val, 
            life_val, hq-> warrior_num[index], names[index].c_str(),
            color_str.c_str());
}


Headquarter::Headquarter(char c){
    char i;
    this->stopped = 0;
    this->cur_index = 0;
    this->color = c;
    this->total_life_val = 0;
    this->total_warrior_val = 1;
    for(i=0; i< WARRIOR_NUM; i++)
        warrior_num[i] = 0;
}

void Headquarter::set_total_life(int tl){
    total_life_val = tl;
}
char Headquarter::produce(int time){
    char i;
    char cnt = 0;
    char lv_index;
   
    if(stopped) return 1;
    //check if life value is used up!
    while(cnt < WARRIOR_NUM){
        i = cur_index + cnt;
        cur_index = i % WARRIOR_NUM;
        lv_index = producing_order[color][cur_index];        
        if(Warrior::life_vals[lv_index] < total_life_val){
            total_life_val -= Warrior::life_vals[lv_index];
            break;
        }
        cnt++;
    }

    // the life value is used up!
    if(cnt == WARRIOR_NUM){
        if(color == 0){
            printf("%03d red headquarter stops making warriors\n", time);
        }else if(color == 1)
            printf("%03d blue headquarter stops making warriors\n", time);
        stopped = 1;
        return 1;
    }

   
    //life value is not used up,  produce warrior
    switch (lv_index){
        case 0:
            pwarrior[total_warrior_val] =  new Dragon(this, 
                                              ++warrior_num[lv_index],
                                               Warrior::life_vals[lv_index], 10);      
            //pp->print_result(time);
            break;
        case 1:
            pwarrior[total_warrior_val] = new Ninja(this, 
                                              ++warrior_num[lv_index],
                                               Warrior::life_vals[lv_index], 10);      
            break;
        case 2:
            pwarrior[total_warrior_val] = new Iceman(this, 
                                              ++warrior_num[lv_index],
                                               Warrior::life_vals[lv_index], 10);      
            break;
        case 3:
            pwarrior[total_warrior_val] = new Lion(this, 
                                              ++warrior_num[lv_index],
                                               Warrior::life_vals[lv_index], 10);      
            break;
        case 4:
            pwarrior[total_warrior_val] = new Warrior(this, 
                                              ++warrior_num[lv_index],
                                               Warrior::life_vals[lv_index], 10);      
            break;
        default:
            break;
     }
    pwarrior[total_warrior_val]->print_result(time);
    total_warrior_val++;

    cur_index++;
    if(cur_index >= WARRIOR_NUM){
        cur_index = 0;
    }
   return 0;
}

string Headquarter::get_color(){
    if(color == 0){
        return "red";
    }else{
        return "blue";
    }
}

Headquarter::~Headquarter(){
    int i;
    for(i=0; i< total_warrior_val; i++){
        delete pwarrior[i];
    }
}

string Warrior::names[WARRIOR_NUM] = {"dragon","ninja","iceman","lion","wolf"};
string Warrior::weapon_names[WEAPON_NUM] = {"sword", "bomb", "arrow"};
char Warrior::life_vals[WARRIOR_NUM];
char Headquarter::producing_order[HEADQUARTER_NUM][WARRIOR_NUM] = {{ 2,3,4,1,0 }, {3,0,1,2,4}}; //producing order

int main(){
    int t;
    int m;
    Headquarter red_hq(0);
    Headquarter blue_hq(1);
    //scanf("Case total number:%d", &t);
    scanf("%d", &t);
    int ncase_num = 1;
    while(t--){
        printf("Case:%d\n",ncase_num++);
        //scanf("Total Life Value:%d", &m);
        scanf("%d", &m);
        red_hq.set_total_life(m);
        blue_hq.set_total_life(m);
        for(int i=0; i< WARRIOR_NUM; i++)
            scanf("%d", & Warrior::life_vals[i]);
        int ntime = 0;
        while(true){
            int tmp1 = red_hq.produce(ntime);
            int tmp2 = blue_hq.produce(ntime);
           // printf("%s ", red_hq.get_color());
           // printf("%s\n", blue_hq.get_color());
            if( tmp1 == 1 && tmp2 == 1)
                break;
            ntime++;
        }
    }   
    return 0;
}

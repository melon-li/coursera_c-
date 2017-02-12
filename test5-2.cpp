#include <iostream>
#include <cstring>
#include <stdint.h>
#include <stdio.h>

using namespace std;
enum WType{DRAGON, NINJA, ICEMAN, LION, WOLF};
enum HType{RED, BLUE};

class HeadQuarter;
const uint8_t WARRIOR_NUM = 5;
const uint8_t HQ_NUM = 2;

class Warrior{
    public:
        static uint8_t inital_lifevals[WARRIOR_NUM]; 
        WType type;
        uint32_t id;
        uint32_t life_force;
        uint32_t fight_force;
        HeadQuarter *hq;
        Warrior *next;
        Warrior(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
                id(_id), life_force(_lf), fight_force(_ff), type(_t), hq(_hq){
            next = NULL;
        } 
};
uint8_t Warrior::inital_lifevals[WARRIOR_NUM] = {0, 0, 0, 0, 0};


class Weapon{
    public:
        static  string weapon_types[3];
        char *name;
        uint32_t id;
        Weapon(char *n, uint32_t i): id(i){
            if(!n){
                name = NULL; 
            }else{
                char *t = new char[strlen(n)];
                strcpy(t, n);
                name = t;
            }
        }
        ~Weapon(){if(name) delete []name;}
};
string  Weapon::weapon_types[3] = {"sword", "bomb", "arrow"}; 


class HeadQuarter{
    public:
        static WType producing_order[2][WARRIOR_NUM];
        HType type;    
        uint32_t total_lf;
        uint32_t total_war;
        uint32_t war_cnt[WARRIOR_NUM];
        Warrior *warrior_lib;
        uint8_t cur_index;
        bool stopped;

        HeadQuarter(HType _t, uint32_t _tlf):type(_t),total_lf(_tlf){
            warrior_lib=NULL;
            cur_index = 0;
            total_war = 0;
            stopped = false;
            for(uint8_t i=0; i<WARRIOR_NUM; i++) war_cnt[i] = 0;
        }

        bool create_warrior(uint32_t time);
        void print_info(uint32_t time, WType type, Warrior *w);
        void set_lifeval(uint32_t lv){total_lf=lv;stopped=false;}
};
WType HeadQuarter::producing_order[HQ_NUM][WARRIOR_NUM] = {{ICEMAN, LION, WOLF, NINJA, DRAGON},
                                           {LION, DRAGON, NINJA, ICEMAN, WOLF}};


class Dragon:public Warrior{
    public:
       Weapon *weapon;
       double morale;
       Dragon(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq),
            morale(double(_hq->total_lf)/double(_lf)){
            weapon = new Weapon(NULL, _id%3);
       }
       ~Dragon(){if(weapon) delete weapon;}
};


class Ninja:public Warrior{
    public:
        Weapon *weapon[2];
        Ninja(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){
            weapon[0] = new Weapon(NULL, _id%3);
            weapon[1] = new Weapon(NULL, (_id+1)%3);
        }
       ~Ninja(){
           if(weapon[0]) delete weapon[0]; 
           if(weapon[1]) delete weapon[1]; 
      }
};


class Iceman:public Warrior{
    public:
        Weapon *weapon;
        Iceman(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){
            weapon = new Weapon(NULL, _id%3);
        }
       ~Iceman(){if(weapon) delete weapon;}
};


class Lion:public Warrior{
    public:
        uint32_t loyalty;
        Lion(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq),
            loyalty( _hq->total_lf){}
};


class Wolf:public Warrior{
    public:
        Wolf(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){}
};


bool HeadQuarter::create_warrior(uint32_t time){
    uint32_t life_val = 0;
    WType wtype;
    uint8_t cnt = 0; 
    if(stopped) return false;
    while(cnt++ < WARRIOR_NUM){
        wtype = producing_order[type][cur_index++];
        if(cur_index >= WARRIOR_NUM) cur_index = 0;
        life_val = Warrior::inital_lifevals[wtype];
        if(life_val <= total_lf){
            total_lf -= life_val; 
            Warrior *wt;
            switch(wtype){
                case DRAGON:
                    wt = new Dragon(total_war+1, life_val, life_val, wtype, this);
                    break;
                case NINJA:
                    wt = new Ninja(total_war+1, life_val, life_val, wtype, this);
                    break;
                case ICEMAN:
                    wt = new Iceman(total_war+1, life_val, life_val, wtype, this);
                    break;
                case LION:
                    wt = new Lion(total_war+1, life_val, life_val, wtype, this);
                    break;
                case WOLF:
                    wt = new Wolf(total_war+1, life_val, life_val, wtype, this);
                    break;
                default:
                   break;
           
            }
            if(warrior_lib == NULL){
                warrior_lib = wt;
            }else{
                warrior_lib->next = wt; 
            }
            war_cnt[wtype]++;
            total_war++;
            print_info(time, wtype, wt);
            return true;
        }
    }
    stopped = true;
    print_info(time, wtype, NULL);
    return false;
}

void HeadQuarter::print_info(uint32_t time, WType wtype, Warrior *w=NULL){
    string hqnames[HQ_NUM] = {"red", "blue"};
    string warnames[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};

    if(stopped){
        printf("%03d %s headquarter stops making warriors\n",
               time,
               hqnames[type].c_str());
        return;
    }
    printf("%03d %s %s %d born with strength %d, %d %s in %s headquarter\n",
            time,
            hqnames[type].c_str(),
            warnames[wtype].c_str(),
            total_war,
            Warrior::inital_lifevals[wtype],
            war_cnt[wtype],
            warnames[wtype].c_str(),
            hqnames[type].c_str());
    switch(wtype){
        case DRAGON:
            printf("It has a %s, and it's morale is %.2f\n",
                  Weapon::weapon_types[((Dragon *)w)->weapon->id].c_str(),
                  ((Dragon *)w)->morale);
            break;
        case NINJA:
            printf("It has a %s and %s\n",
                  Weapon::weapon_types[((Ninja *)w)->weapon[0]->id].c_str(),
                  Weapon::weapon_types[((Ninja *)w)->weapon[1]->id].c_str());
            break;
        case ICEMAN:
            printf("It has a %s\n",
                  Weapon::weapon_types[((Iceman *)w)->weapon->id].c_str());
            break;
        case LION:
            printf("It's loyalty is %d\n",
                  ((Lion *)w)->loyalty);
            break;
        case WOLF:
            break;
        default:
           break;
   
    }
}

int main(){
    uint32_t group_num = 0;
    uint32_t total_lifevals = 0;
    uint32_t time_seq = 0;
    bool rflag = false;
    bool bflag = false;
    uint32_t cnt = 0; 

    cin>>group_num;
    cin>>total_lifevals;
    HeadQuarter rhq(RED, total_lifevals);
    HeadQuarter bhq(BLUE, total_lifevals);
    for(uint8_t i=0; i<WARRIOR_NUM; i++)scanf("%d", &Warrior::inital_lifevals[i]);
    cout<<"Case:"<<group_num<<endl;
    cnt = total_lifevals;
    time_seq = 0;
    while(cnt--){
        rflag = rhq.create_warrior(time_seq);
        bflag = bhq.create_warrior(time_seq++);
        if(!rflag && !bflag ) break;
    }
    return 0;
}

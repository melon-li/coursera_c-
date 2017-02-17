#include <iostream>
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <queue>

using namespace std;
enum WType{DRAGON, NINJA, ICEMAN, LION, WOLF};
enum WeaponType{SWORD, BOMB, ARROW};
enum HType{RED, BLUE, NONE};

const uint8_t WARRIOR_NUM = 5;
const uint8_t HQ_NUM = 2;

class Warrior;
class Weapon;
class City;
class PriorityWarrior;


class HeadQuarter{
    public:
        static WType producing_order[2][WARRIOR_NUM];
        static string hqnames[HQ_NUM];
        HType type;    
        uint32_t total_lf;
        uint32_t total_war;
        uint32_t war_cnt[WARRIOR_NUM];
        Warrior *warrior_lib;
        City *city;
        uint8_t cur_index;
        uint32_t cur_min;
        uint32_t reached;
        bool stopped;

        HeadQuarter(HType _t, uint32_t _tlf, City *c):
            type(_t), total_lf(_tlf), city(c){
            warrior_lib=NULL;
            cur_index = 0;
            cur_min = 0;
            total_war = 0;
            reached=0;
            stopped = false;
            for(uint8_t i=0; i<WARRIOR_NUM; i++) war_cnt[i] = 0;
        }

        bool create_warrior(uint32_t min);
        bool flee(City *ehqc, uint32_t min);
        void set_lifeval(uint32_t lv){total_lf=lv;stopped=false;}
        bool gostep(HeadQuarter *ehq, uint32_t min);
        void take_lifesourcer(uint32_t min);
        void release_arrows(HeadQuarter *ehq, uint32_t min);
        void perish_together(HeadQuarter *ehq, uint32_t min);
        void delete_warrior(Warrior *w);
        void attack(HeadQuarter *ehq, uint32_t min);
        void award(priority_queue <PriorityWarrior> pq);
        void award(priority_queue <PriorityWarrior, vector<PriorityWarrior>, greater<PriorityWarrior> > pq);
        void rob_lifesourcer(priority_queue <PriorityWarrior> pq);
        void rob_lifesourcer(priority_queue <PriorityWarrior, vector<PriorityWarrior>, greater<PriorityWarrior> > pq);
        void report_life_force(uint32_t min);
        void report_weapons(uint32_t min);
};
WType HeadQuarter::producing_order[HQ_NUM][WARRIOR_NUM] = {{ICEMAN, LION, WOLF, NINJA, DRAGON},
                                           {LION, DRAGON, NINJA, ICEMAN, WOLF}};
string HeadQuarter::hqnames[HQ_NUM] = {"red", "blue"};


class City{
    public:
        static uint32_t total;
        uint32_t lifesourcer;
        uint32_t id;
        uint32_t total_warrior;
        HType banner;
        int8_t red_cnt;
        int8_t blue_cnt;
        
        City(uint32_t _id):id(_id){
            lifesourcer = 0;
            total_warrior = 0;
            red_cnt = 0;
            blue_cnt = 0;
            total++;
            banner = NONE;
        }
        City(){
            lifesourcer = 0;
            total_warrior = 0;
            red_cnt = 0;
            blue_cnt = 0;
            id = total;
            total++;
            banner = NONE;
        }
        City(const City &c){
            lifesourcer = c.lifesourcer;
            red_cnt = c.red_cnt;
            blue_cnt = c.blue_cnt;
            total_warrior = c.total_warrior;
            banner = c.banner;
            id = c.id;
            total++;
        }
        ~City(){total--;}

        bool gen_lifesourcer(){
            lifesourcer += 10;
        }

        uint32_t takeaway_lifesourcer(){
            uint32_t t = lifesourcer; 
            lifesourcer = 0;
            return t;
        }

        void insert_banner(HeadQuarter *hq);

        void descrease_warrior(){
            if(total_warrior > 0){
                total_warrior--;
            }else{
                total_warrior = 0;
            }
        }
        void increase_warrior(){total_warrior++;}
        bool isalone(){
            if(total_warrior == 1)return true;
            return false;
        }

};
uint32_t City::total = 0;


void City::insert_banner(HeadQuarter *hq){
    if(hq == NULL){
        red_cnt = 0;
        blue_cnt = 0;
    }else if(hq->type == RED){
        red_cnt++;
        blue_cnt = 0;
    }else if(hq->type == BLUE){
        blue_cnt++;
        red_cnt = 0;
    }
    if(red_cnt >=2 || blue_cnt >=2){
        blue_cnt = red_cnt = 0;
        if(banner == hq->type) return;
        banner = hq->type;
        printf("%03d:%02d %s flag raised in city %d\n",
            hq->cur_min/60,
            hq->cur_min%60,
            HeadQuarter::hqnames[hq->type].c_str(),
            id);
    }
}


class Weapon{
    public:
        static  string weapon_types[3];
        char *name;
        uint32_t id;
        uint32_t fight_force;
        Warrior *warrior;
        Weapon *next;
        Weapon(char *n, uint32_t i, Warrior *w): 
            id(i),
            warrior(w){
            fight_force = 0;
            next = NULL;
            if(!n){
                name = NULL; 
            }else{
                char *t = new char[strlen(n)];
                strcpy(t, n);
                name = t;
            }
        }
        Weapon(Weapon *w){
            name = NULL;
            id = 0;
            fight_force = 0;
            warrior = NULL;
            next = NULL;
            if(w){
                char *t =  new char[strlen(w->name)+1];
                strcpy(t, w->name);
                name = t;
                id = w->id;
                fight_force = w->fight_force;
                warrior = w->warrior;
            }
        }
        ~Weapon(){if(name) delete []name;}
};
string  Weapon::weapon_types[3] = {"sword", "bomb", "arrow"}; 


class Warrior{
    public:
        static uint32_t inital_lifevals[WARRIOR_NUM]; 
        static uint32_t inital_fightvals[WARRIOR_NUM]; 
        static string warnames[WARRIOR_NUM];
        WType type;
        uint32_t id;
        uint32_t life_force;
        uint32_t fight_force;
        uint32_t step;
        HeadQuarter *hq;
        Weapon *weapon;
        Warrior *next;
        City *city;
        bool reached;
        Warrior(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
                id(_id), life_force(_lf), fight_force(_ff), type(_t), hq(_hq){
            city = hq->city;
            city->increase_warrior();
            weapon = NULL;
            next = NULL;
            step = 0;
            reached = false;
            printf("%03d:%02d %s %s %d born\n", 
                hq->cur_min/60,
                hq->cur_min%60,
                HeadQuarter::hqnames[hq->type].c_str(),
                Warrior::warnames[type].c_str(),
                hq->total_war,
                Warrior::inital_lifevals[type],
                hq->war_cnt[type],
                Warrior::warnames[type].c_str(),
                HeadQuarter::hqnames[hq->type].c_str());
        } 
        ~Warrior(){
            city->descrease_warrior();
            Weapon *t = weapon;
            while(t){
                if(t){
                    delete t;
                    t = weapon->next;
                }
            }
        }
        virtual bool attack(Warrior *e);
        virtual bool fight_back(Warrior *e);
        virtual bool hurt(Warrior *e);
        virtual uint32_t get_weaponforce();
        virtual void go(HeadQuarter *ehq, City *c);
        bool isproactive();

};
uint32_t Warrior::inital_lifevals[WARRIOR_NUM] = {0, 0, 0, 0, 0}; 
uint32_t Warrior::inital_fightvals[WARRIOR_NUM] = {0, 0, 0, 0, 0}; 
string Warrior::warnames[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};


class PriorityWarrior{
    public:
        static uint32_t index;
        City *city;
        Warrior *warrior;
        uint32_t id;
        PriorityWarrior(City *c, Warrior *w){
            id = index;
            city = c;
            warrior = w;
            index++;
        }

        PriorityWarrior(const PriorityWarrior &pw){
            id = index;
            city = pw.city;
            warrior = pw.warrior;
            index++;
        }

        bool operator <(const PriorityWarrior &pw) const{
            if(city->id < (pw.city)->id) return true;
            if(id < pw.id) return true;
            return false;
        }

        bool operator >(const PriorityWarrior &pw) const{
            if(city->id > (pw.city)->id) return true;
            if(id > pw.id) return true;
            return false;
        }

        PriorityWarrior & operator=(const PriorityWarrior *pw){
            id = index;
            city = pw->city;
            warrior = pw->warrior;
            index++;
        }
};
uint32_t  PriorityWarrior::index = 0;


class PriorityWeapon{
    public:
        static uint32_t index;
        Weapon *weapon;
        uint32_t id;
        PriorityWeapon(Weapon *we): weapon(we){id = index;index++;}
        PriorityWeapon(const PriorityWeapon &pwe){
            id = index;
            weapon = pwe.weapon;
            index++;
        }
        bool operator <(const PriorityWeapon & pwe) const{
            if(weapon->id < (pwe.weapon)->id) return  true;
            if(id < pwe.id) return true;
            return false;
        }
        bool operator >(const PriorityWeapon & pwe) const{
            if(weapon->id > (pwe.weapon)->id) return  true;
            if(id > pwe.id) return true;
            return false;
        }
};
uint32_t PriorityWeapon::index =0;

class Sword: public Weapon{
    public:
        Sword(char *n, uint32_t _id,  Warrior *w):
            Weapon(n, _id, w){
            fight_force= w->fight_force/5;
        }

        Sword(Sword *s):Weapon(s){}
        bool blunt(){
            fight_force = (fight_force*4)/5; 
            if(fight_force <=0) return false; //Sword becomes invalid.
            return true;
        }
};


class Arrow: public Weapon{
    public:
        static uint32_t R;
        int8_t used;
        Arrow(char *n, uint32_t _id, Warrior *w):
            Weapon(n, _id, w){
                used = 0;
            }
        Arrow(Arrow *a):Weapon(a){
            used = 0;
            if(a) used = a->used;
        }
        bool shoot(Warrior *e){
            if(used > 3)return false; // Arrow becomes invalid.
            int32_t t = e->life_force - R;
            e->life_force = t > 0 ? t: 0;
            used++;
            if(t<=0)return true; //Enemy is killed by arrow.
            return false;
        }
};
uint32_t Arrow::R = 0;


class Bomb: public Weapon{
    public:
        Bomb(char *n, uint32_t _id, Warrior *w):Weapon(n, _id, w){}
        Bomb(Bomb *b):Weapon(b){}
        //Bomb donot consider the fight_force of sword of enemy?
        bool perish_together(Warrior *enemy, bool isproactive);
};

bool Bomb::perish_together(Warrior *enemy,  bool isproactive){
    bool f = false;
    uint32_t ff = 0;

    // Attack enemy proatively.
    if(isproactive){
        for(Weapon *we=warrior->weapon; we!=NULL; we=we->next){
            if(we->id == SWORD){
                ff = we->warrior->get_weaponforce();
                break;
            }
        }
        int32_t elf = enemy->life_force - warrior->fight_force - ff;
        if(elf > 0){
            ff = 0;
            for(Weapon *we=enemy->weapon; we!=NULL; we=we->next){
                if(we->id == SWORD){
                    ff = we->warrior->get_weaponforce();
                    break;
                }
            }
            if(warrior->life_force <= (enemy->life_force/2 + ff)) f= true;
        }
    }else{
    // Attack enemy negatively.
        for(Weapon *we=enemy->weapon; we!=NULL; we=we->next){
            if(we->id == SWORD){
                ff = we->warrior->get_weaponforce();
                break;
            }
        }
        if(warrior->life_force <= (enemy->fight_force + ff)){
            f = true;
        }
    }
    if(f){
        warrior->life_force = 0;
        enemy->life_force = 0;
    }
    return f;
}


class Dragon:public Warrior{
    public:
        double morale;
        Dragon(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq),
            morale(double(_hq->total_lf)/double(_lf)){
            weapon = new Weapon(NULL, _id%3, this);
            printf("It's morale is %.2f\n", morale);
        }
        virtual bool attack(Warrior *e);
        void yell(City *c){
            if(life_force < 0 && morale > 0.8){
                printf("%03d:%02d %s dragon %d yelled in city %d\n",
                    hq->cur_min/60,
                    hq->cur_min%60,
                    HeadQuarter::hqnames[hq->type].c_str(),
                    id,
                    c->id);
            }
        }
};


class Ninja:public Warrior{
    public:
        Ninja(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){
            weapon = new Weapon(NULL, _id%3, this);
            weapon->next = new Weapon(NULL, (_id+1)%3, this);
            printf("It has a %s and %s\n",
                  Weapon::weapon_types[weapon->id].c_str(),
                  Weapon::weapon_types[weapon->next->id].c_str());
        }
        virtual bool hurt(Warrior *e);
};


class Iceman:public Warrior{
    public:
        Weapon *weapon;
        Iceman(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){
            weapon = new Weapon(NULL, _id%3, this);
            printf("It has a %s\n",
                  Weapon::weapon_types[weapon->id].c_str());
        }
        virtual void go(HeadQuarter *ehq, City *c);
};


class Lion:public Warrior{
    public:
        static int32_t K;
        int32_t loyalty;
        Lion(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq),
            loyalty( _hq->total_lf){
            printf("It's loyalty is %d\n", loyalty);
        }
        virtual bool attack(Warrior *e);
        virtual bool hurt(Warrior *e);
        virtual bool fight_back(Warrior *e);
        bool flee(City *ehqc);
};
int32_t Lion::K = 0;


class Wolf:public Warrior{
    public:
        
        Wolf(uint32_t _id, uint32_t _lf, uint32_t _ff, WType _t, HeadQuarter *_hq):
            Warrior(_id, _lf, _ff, _t, _hq){}
        virtual bool attack(Warrior *e);
        virtual bool fight_back(Warrior *e);
        void rob_weapon(Warrior *e);
};


bool Warrior::attack(Warrior *e){
    if(life_force <= 0) return false;
    printf("%03d:%02d %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
        hq->cur_min/60,
        hq->cur_min%60,
        HeadQuarter::hqnames[hq->type].c_str(),
        Warrior::warnames[type].c_str(),
        id,
        HeadQuarter::hqnames[e->hq->type].c_str(),
        Warrior::warnames[e->type].c_str(),
        e->id,
        city->id,
        city->lifesourcer,
        fight_force);
    bool r = e->hurt(this);
    return r;
}

bool Warrior::hurt(Warrior *e){
    uint32_t wf = e->get_weaponforce();
    int32_t t = life_force - (wf+e->fight_force);
    life_force = t > 0? t: 0;
    if(life_force == 0) return true;
    fight_back(e);
    return false;
}

bool Warrior::fight_back(Warrior *e){
    if(life_force <= 0) return false;
    printf("%03d:%02d %s %s %d fought back against %s %s %d in city %d\n",
        hq->cur_min/60,
        hq->cur_min%60,
        HeadQuarter::hqnames[hq->type].c_str(),
        Warrior::warnames[type].c_str(),
        id,
        HeadQuarter::hqnames[e->hq->type].c_str(),
        Warrior::warnames[e->type].c_str(),
        e->id,
        city->id);
    uint32_t wf = get_weaponforce();
    int32_t t = e->life_force - fight_force/2 - wf;
    e->life_force = t > 0 ? t: 0;
    if(t <=0 ) return true;
    return false;
}

uint32_t Warrior::get_weaponforce(){
    uint32_t sf = 0;
    uint32_t tmp = 0;
    for(Weapon *t=weapon; t!=NULL; t=weapon->next)
        tmp = t->id == uint32_t(SWORD) ? t->fight_force: 0;
        sf += tmp;
    return sf;
}

void Warrior:: go(HeadQuarter *ehq, City *c){
    city->descrease_warrior();
    c->increase_warrior();
    city = c;
    step++;
    if(city != ehq->city){
        printf("%03d:%02d %s %s %d marched to city %d with %d elements and force %d\n",
            hq->cur_min/60,
            hq->cur_min%60,
            HeadQuarter::hqnames[hq->type].c_str(),
            Warrior::warnames[type].c_str(),
            id,
            city->id,
            city->lifesourcer,
            fight_force);
    }else{
        reached = true;
    }
}

bool Warrior::isproactive(){
    if((city->id%2 == 1 && city->banner == NONE) ||
        city->banner == RED){
        if(hq->type == RED) return true;
    }else if ((city->id%2 == 0 && city->banner == NONE) ||
        city->banner == BLUE){
        if(hq->type == BLUE) return true;
    }
    return false;
}

bool Dragon::attack(Warrior *e){
    if(life_force <= 0) return false;
    bool r = e->hurt(this);
    if(r){
        morale += 0.2;
    }else{
        morale -= 0.2;
    }
    yell(city);
    return r;
}


bool Ninja::hurt(Warrior *e){
    uint32_t wf = e->get_weaponforce();
    int32_t t = life_force - (wf+e->fight_force);
    life_force = t > 0? t: 0;
    if(life_force == 0) return true;
    return false;
}

void Iceman::go(HeadQuarter *ehq, City *c){
    Warrior::go(ehq, c);
    if(step%2 == 0 && step != 0){
        int32_t t = life_force - 9;
        life_force = t > 1 ? t: 1;
        fight_force += 20;
    }
}

bool Lion::attack(Warrior *e){
    if(life_force <= 0) return false;
    bool r = e->hurt(this);
    if(!r) loyalty -= K;
    return r;
}

bool Lion::hurt(Warrior *e){
    uint32_t wf = e->get_weaponforce();
    uint32_t lf_bak = life_force; 
    int32_t t = life_force - (wf+e->fight_force);
    life_force = t > 0? t: 0;
    if(life_force == 0){
        e->life_force += lf_bak;
        return true;
    }
    fight_back(e);
    return false;
}

bool Lion::fight_back(Warrior *e){
    if(life_force <= 0){
        loyalty -= K;
        return false;
    }
    uint32_t wf = get_weaponforce();
    int32_t t = e->life_force - fight_force/2 - wf;
    e->life_force = t > 0 ? t: 0;
    if(t <=0 ) return true;
    loyalty -= K;
    return false;
}

bool Lion::flee(City *ehqc){
    if(city == ehqc) return false;
    if(loyalty <= 0){
        printf("%03d:%02d %s lion %d ran away\n",
            hq->cur_min/60,
            hq->cur_min%60,
            HeadQuarter::hqnames[hq->type].c_str(),
            id);
        return true;
    }
}


bool Wolf::attack(Warrior *e){
    if(life_force <= 0) return false;
    bool r = e->hurt(this);
    if(r) rob_weapon(e);
    return r;
}


bool Wolf::fight_back(Warrior *e){
    if(life_force <= 0) return false;
    uint32_t wf = get_weaponforce();
    int32_t t = e->life_force - fight_force/2 - wf;
    e->life_force = t > 0 ? t: 0;
    if(t <=0 ) {rob_weapon(e);return true;}
    return false;
}

void Wolf::rob_weapon(Warrior *e){
    Weapon *t, *t2;

    for(*t=e->weapon; t!=NULL; t=e->weapon->next){
        bool flag = false;
        for(*t2=weapon; t2!=NULL; t2=weapon->next)
            if(t->id == t2->id){flag = true; break;}
        if(flag) continue;
        switch(t->id){
            case SWORD:
                t2 = new Sword((Sword *)t);
                break;

            case ARROW:
                t2 = new Arrow((Arrow *)t);
                break;

            case BOMB:
                t2 = new Bomb((Bomb *)t);
                break;
            default:
                break;
        }
        t2->warrior = this;
        if(!weapon) weapon = t2;
        if(weapon) weapon->next = t2;
    }
}


//bool HeadQuarter::create_warrior(uint32_t min){
    //uint32_t life_val = 0;
    //uint32_t fight_val = 0;
    //WType wtype;
    //uint8_t cnt = 0; 
    //cur_min = min;
    //if(stopped) return false;
    //while(cnt++ < WARRIOR_NUM){
        //wtype = producing_order[type][cur_index++];
        //if(cur_index >= WARRIOR_NUM) cur_index = 0;
        //life_val = Warrior::inital_lifevals[wtype];
        //fight_val = Warrior::inital_fightvals[wtype];
        //if(life_val <= total_lf){
            //total_lf -= life_val; 
            //Warrior *wt;
            //war_cnt[wtype]++;
            //total_war++;
            //switch(wtype){
                //case DRAGON:
                    //wt = new Dragon(total_war, life_val, fight_val, wtype, this);
                    //break;
                //case NINJA:
                    //wt = new Ninja(total_war, life_val, fight_val, wtype, this);
                    //break;
                //case ICEMAN:
                    //wt = new Iceman(total_war, life_val, fight_val, wtype, this);
                    //break;
                //case LION:
                    //wt = new Lion(total_war, life_val, fight_val, wtype, this);
                    //break;
                //case WOLF:
                    //wt = new Wolf(total_war, life_val, fight_val, wtype, this);
                    //break;
                //default:
                   //break;
           
            //}
            //if(warrior_lib == NULL){
                //warrior_lib = wt;
            //}else{
                //warrior_lib->next = wt; 
            //}
             //return true; 
        //}
    //}
    //stopped = true;
    //if(stopped){
        //printf("%03d %s headquarter stops making warriors\n",
               //min,
               //HeadQuarter::hqnames[type].c_str());
    //}
    //return false;
//}

bool HeadQuarter::create_warrior(uint32_t min){
    uint32_t life_val = 0;
    uint32_t fight_val = 0;
    WType wtype;
    cur_min = min;
    if(stopped) return false;

    //printf("city->id=%d\n", city->id);
    wtype = producing_order[type][cur_index];
    life_val = Warrior::inital_lifevals[wtype];
    fight_val = Warrior::inital_fightvals[wtype];
    if(life_val <= total_lf){
        cur_index++;
        if(cur_index >= WARRIOR_NUM) cur_index = 0;
        total_lf -= life_val; 
        Warrior *wt;
        war_cnt[wtype]++;
        total_war++;
        switch(wtype){
            case DRAGON:
                wt = new Dragon(total_war, life_val, fight_val, wtype, this);
                break;
            case NINJA:
                wt = new Ninja(total_war, life_val, fight_val, wtype, this);
                break;
            case ICEMAN:
                wt = new Iceman(total_war, life_val, fight_val, wtype, this);
                break;
            case LION:
                wt = new Lion(total_war, life_val, fight_val, wtype, this);
                break;
            case WOLF:
                wt = new Wolf(total_war, life_val, fight_val, wtype, this);
                break;
            default:
               break;
       
        }
        if(warrior_lib == NULL){
            warrior_lib = wt;
        }else{
            warrior_lib->next = wt; 
        }
         return true; 
    }

    return false;
}

bool HeadQuarter::flee(City *ehqc, uint32_t min){
    bool f = false;
    cur_min = min;
    Warrior *pw = warrior_lib;
    for(Warrior *w=warrior_lib; w!=NULL; w=w->next){
        if(w->type != LION) {pw=w; continue;}
        f = ((Lion *)w)->flee(ehqc);
        if(!f){pw=w; continue;}
        Warrior *next= w->next;
        delete w;
        w = next;
        pw->next = w;
        w = pw;
    }
}

bool HeadQuarter::gostep(HeadQuarter *ehq, uint32_t min){
    cur_min = min;
    for(Warrior *w=warrior_lib; w!=NULL; w=w->next){
        if(w->city == ehq->city) continue;
        if(type == RED)w->go(ehq, w->city + 1);
        if(type == BLUE)w->go(ehq, w->city - 1);
        if(w->city == ehq->city){
            reached++;
            printf("%03d:%02d  %s %s %d reached %s headquarter with %d elements and force %d\n",
                cur_min/60,
                cur_min%60,
                HeadQuarter::hqnames[type].c_str(),
                Warrior::warnames[w->type].c_str(),
                w->id,
                HeadQuarter::hqnames[ehq->type].c_str(),
                w->life_force,
                w->fight_force);
            if(reached>=2){
                printf("%03d:%02d %s headquarter was taken\n",
                    cur_min/60,
                    cur_min%60,
                    HeadQuarter::hqnames[ehq->type].c_str());
                return true;
            }
        }
    }
    return false;
}

void HeadQuarter::take_lifesourcer(uint32_t min){
    cur_min = min;
    for(Warrior *w=warrior_lib; w!=NULL; w=w->next){
        if(w->city->isalone() && w->reached == false){
            uint32_t ls = w->city->takeaway_lifesourcer();
            total_lf += ls;
            if(ls)
                printf("%03d:%02d %s %s %d earned %d elements for his headquarter\n",
                    cur_min/60,
                    cur_min%60,
                    HeadQuarter::hqnames[type].c_str(),
                    Warrior::warnames[w->type].c_str(),
                    w->id,
                    ls);
        }
    }
}

void HeadQuarter::release_arrows(HeadQuarter *ehq, uint32_t min){
    City *n;
    Warrior *w;
    Warrior *ew;
    cur_min = min;
    for(w=warrior_lib; w!=NULL; w=w->next){
       if(w->city == ehq->city) continue;
       if(type == RED){
           n = w->city + 1;
       }else if (type == BLUE){
           n = w->city - 1;
       }
       if(n == ehq->city) continue;

       for(ew=ehq->warrior_lib; ew!=NULL; ew=ew->next){
           if(ew->city == n) break;
       }
       if(ew == NULL) continue;
       if(ew->city != n) continue;

       for(Weapon *we=w->weapon; we!=NULL; we=we->next){
           if(we->id != ARROW) continue;
           bool f = ((Arrow *)we)->shoot(ew);
           printf("%03d:%02d %s %s %d shot",
                cur_min/60,
                cur_min%60,
                HeadQuarter::hqnames[type].c_str(),
                Warrior::warnames[w->type].c_str(),
                w->id);
           if(f)
               printf(" and killed %s %s %d\n",
                   HeadQuarter::hqnames[ehq->type].c_str(),
                   Warrior::warnames[ew->type].c_str(),
                   ew->id);
       }
    }
}

void HeadQuarter::perish_together(HeadQuarter *ehq, uint32_t min){
    Warrior *w;
    Warrior *ew;
    bool f = false;
    cur_min = min;
    for(w=warrior_lib; w!=NULL; w=w->next){
        f = false;
        if(w->city == city) continue;
        for(ew=ehq->warrior_lib; ew!=NULL; ew=ew->next){
            if(w->city == ew->city){
                for(Weapon *we=w->weapon; we!=NULL; we=we->next){
                    if(we->id != BOMB) continue;
                    f = ((Bomb *)we)->perish_together(ew, w->isproactive());
                }
                break;
            }
        }
        if(!f) continue;
        printf("%03d:%02d %s %s %d used a bomb and killed %s %s %d\n",
            cur_min/60,
            cur_min%60,
            HeadQuarter::hqnames[type].c_str(),
            Warrior::warnames[w->type].c_str(),
            w->id,
            HeadQuarter::hqnames[ehq->type].c_str(),
            Warrior::warnames[ew->type].c_str(),
            ew->id);
        delete_warrior(w);
        ehq->delete_warrior(ew);
    }

}

void HeadQuarter::delete_warrior(Warrior *w){
    Warrior *pi = warrior_lib;
    if(w == warrior_lib){
        warrior_lib = warrior_lib->next;
        delete pi;
        return;
    }
    for(Warrior *i=warrior_lib; i!=NULL; i=i->next){
        if(i != w) {pi=i; continue;}
        pi->next = i->next;
        delete i;
        break;
    }
}

void HeadQuarter::attack(HeadQuarter *ehq, uint32_t min){
    Warrior *w;
    Warrior *ew;
    City *c;
    priority_queue <PriorityWarrior> pq;
    priority_queue <PriorityWarrior, 
        vector<PriorityWarrior>, 
        greater<PriorityWarrior> > epq;
    bool f = false;
    cur_min = min;
    for(w=warrior_lib; w!=NULL; w=w->next){
        c = w->city;
        for(ew=ehq->warrior_lib; ew!=NULL; ew=ew->next){
            if(w->city != ew->city) continue;
            if((c->id%2 ==  1 && c->banner == NONE) ||
                (c->banner == RED)){
                if(type == RED) w->attack(ew);
                if(type == BLUE) ew->attack(w);
            }else if((c->id%2 == 0 && c->banner == NONE) ||
                (c->banner == BLUE)){
                if(type == BLUE) w->attack(ew);
                if(type == RED) ew->attack(w);
            }
            if(w->life_force <= 0){
                printf("%03d:%02d %s %s %d was killed in city %d\n",
                    cur_min/60,
                    cur_min%60,
                    HeadQuarter::hqnames[type].c_str(),
                    Warrior::warnames[w->type].c_str(),
                    w->id,
                    c->id);
                epq.push(PriorityWarrior(c, ew));
                c->insert_banner(ehq);
                delete_warrior(w);
            }
            if(ew->life_force <= 0){
                printf("%03d:%02d %s %s %d was killed in city %d\n",
                    cur_min/60,
                    cur_min%60,
                    HeadQuarter::hqnames[ew->hq->type].c_str(),
                    Warrior::warnames[ew->type].c_str(),
                    ew->id,
                    c->id);
                pq.push(PriorityWarrior(c, w));
                c->insert_banner(this);
                ehq->delete_warrior(ew);
            }
            c->insert_banner(NULL);
            break; 
        }
    }
    award(pq);
    rob_lifesourcer(pq);
    ehq->award(epq);
    ehq->rob_lifesourcer(epq);
}

void HeadQuarter::award(priority_queue <PriorityWarrior> pq){
    while(!pq.empty()){
        const PriorityWarrior &pw = pq.top();
        if(total_lf - 8 >=0){
            total_lf -= 8;
            pw.warrior->life_force += 8;
            pq.pop();
        }
        if(total_lf <= 0) break;

    }
}

void HeadQuarter::rob_lifesourcer(priority_queue <PriorityWarrior> pq){
    while(!pq.empty()){
        const PriorityWarrior &pw = pq.top();
        uint32_t ls = pw.city->takeaway_lifesourcer();
        total_lf += ls;
        pq.pop();
    }
}
 
void HeadQuarter::award(priority_queue <
    PriorityWarrior, 
    vector<PriorityWarrior>,
    greater<PriorityWarrior> > pq){
    while(!pq.empty()){
        const PriorityWarrior &pw = pq.top();
        if(total_lf - 8 >=0){
            total_lf -= 8;
            pw.warrior->life_force += 8;
            pq.pop();
        }
        if(total_lf <= 0) break;

    }
}

void HeadQuarter::rob_lifesourcer(priority_queue <
    PriorityWarrior,
    vector<PriorityWarrior>,
    greater<PriorityWarrior> > pq){
    while(!pq.empty()){
        const PriorityWarrior &pw = pq.top();
        uint32_t ls = pw.city->takeaway_lifesourcer();
        total_lf += ls;
        pq.pop();
    }
}

void HeadQuarter::report_life_force(uint32_t min){
    cur_min = min;
    printf("%03d:%02d %d elements in %s headquarter\n",
        cur_min/60,
        cur_min%60,
        total_lf,
        HeadQuarter::hqnames[type].c_str());
}

void HeadQuarter::report_weapons(uint32_t min){
    priority_queue <PriorityWarrior, 
        vector<PriorityWarrior>, 
        greater<PriorityWarrior> > pq;
    priority_queue <PriorityWeapon> pq_we;
    Warrior *w;
    Weapon *we;
    cur_min = min;
    
    for(w=warrior_lib; w!=NULL; w=w->next){
        pq.push(PriorityWarrior(w->city, w));
    }
    while(!pq.empty()){
        const PriorityWarrior & pw = pq.top();
        w = pw.warrior;
        for(we=w->weapon; we!=NULL; we=we->next)
            pq_we.push(PriorityWeapon(we));
        printf("%03d:%02d %s %s %d has ",
            cur_min/60,
            cur_min%60,
            HeadQuarter::hqnames[type].c_str(),
            Warrior::warnames[w->type].c_str(),
            w->id);
        if(pq_we.empty()){
            printf("no weapon\n");
            pq.pop();
            continue;
        }
        while(!pq_we.empty()){
            const PriorityWeapon &pwe = pq_we.top();
            we = pwe.weapon;
            if(we->id == ARROW)
                printf("%s(%d)", Weapon::weapon_types[we->id].c_str(), (3- ((Arrow *)we)->used));
            if(we->id == BOMB)
                printf("%s", Weapon::weapon_types[we->id].c_str());
            if(we->id == SWORD)
                printf("%s(%d)", Weapon::weapon_types[we->id].c_str(), we->fight_force);
            pq_we.pop();
            if(!pq_we.empty())printf(",");
        }
        printf("\n");
        pq.pop();
    }
}


int main(){
    uint32_t group_num = 0;
    uint32_t M, N, R, K, T;
    uint32_t fight_forces[WARRIOR_NUM];
    bool rflag = false;
    bool bflag = false;
    uint32_t min = 0;

    cin>>group_num;
    cin >> M >> N >> R >> K >> T;
    City city[N+2];
    HeadQuarter rhq(RED, M, &city[0]);
    HeadQuarter bhq(BLUE, M, &city[N+1]);
    Arrow::R = R;
    Lion::K = K;
    for(uint8_t i=0; i<WARRIOR_NUM; i++)scanf("%d", &Warrior::inital_lifevals[i]);
    for(uint8_t i=0; i<WARRIOR_NUM; i++)scanf("%d", &Warrior::inital_fightvals[i]);
    cout<<"Case:"<<group_num<<endl;
    while(T--){
        uint32_t tmp = min%60;
        switch(tmp){
            case 0:
                rhq.create_warrior(min);
                bhq.create_warrior(min);
                break;
            case 5:
                rhq.flee(bhq.city, min);
                bhq.flee(rhq.city, min);
                break;

            case 10:
                rflag = rhq.gostep(&bhq, min);
                bflag = bhq.gostep(&rhq, min);
                break;

            case 20:
                for(uint32_t i=0; i<(N+2); i++)
                    city[i].gen_lifesourcer();
                break;

            case 30:
                rhq.take_lifesourcer(min);
                bhq.take_lifesourcer(min);
                break;

            case 35:
                rhq.release_arrows(&bhq, min);
                bhq.release_arrows(&rhq, min);
                break;

            case 38:
                rhq.perish_together(&bhq, min);
                bhq.perish_together(&rhq, min);
                break;

            case 40:
                rhq.attack(&bhq, min);
                bhq.attack(&rhq, min);
                break;

            case 50:
                rhq.report_life_force(min);
                bhq.report_life_force(min);
                break;

            case 55:
                rhq.report_weapons(min);
                bhq.report_weapons(min);
                break;

            default:
                break;

        }
        if(rflag || bflag ) break;
        min++;
    }
    return 0;
}

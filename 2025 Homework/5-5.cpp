#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <utility>
using namespace std;
static int currentTime=0;
static bool redConquered=false;
static bool blueConquered=false;
string getTime()
{
    char buffer[10];
    int minute=currentTime%60;
    int hour=currentTime/60;
    sprintf(buffer,"%03d:%02d",hour,minute);
    return string(buffer);
}
class Fighter;
class WeaponBase
{
public:
    string weaponName;
    WeaponBase(const string &name_):weaponName(name_) {}
    virtual void strike(Fighter *attacker,Fighter *victim){}
    virtual bool isUsable()
    {
        return false;
    }
};
class Fighter
{
public:
    int attack;
    int pos;
    string team;
    string type;
    int fighterId;
    int life;
    int currentWeapon;
    vector<WeaponBase*> arms;
    Fighter(int id,int initLife,const string &tm,const string &tp,int position,int atk):fighterId(id),life(initLife),attack(atk),team(tm),type(tp),pos(position),currentWeapon(0)
    {
        arms=vector<WeaponBase*>(10,nullptr);
    }
    Fighter(const Fighter&f)
    {
        type=f.type;
        team=f.team;
        pos=f.pos;
        life=f.life;
        fighterId=f.fighterId;
        attack=f.attack;
        arms=move(f.arms);
    }
    virtual void advance()
    {
        int dir=(team=="red")?1:-1;
        pos+=dir;
        printf("%s %s %s %d marched to city %d with %d elements and force %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,pos,life,attack);
    }
    void captureHQ()
    {
        if(type=="iceman") life-=life/10;
        string enemyTeam;
        if(team=="blue") enemyTeam="red";
        else enemyTeam="blue";
        printf("%s %s %s %d reached %s headquarter with %d elements and force %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,enemyTeam.c_str(),life,attack);
        printf("%s %s headquarter was taken\n",getTime().c_str(),enemyTeam.c_str());
        if(enemyTeam=="red") redConquered=true;
        else blueConquered=true;
    }
    void arrangeArms(bool useUsedFirst);
    int countArms()
    {
        int count=0;
        for(auto wp:arms)
        {
            if(wp!=nullptr) count++;
            else break;
        }
        return count;
    }
    void purgeArms()
    {
        for(int i=0;i<10;i++)
        {
            if(arms[i]!=nullptr&&!arms[i]->isUsable())
            {
                delete arms[i];
                arms[i]=nullptr;
            }
        }
    }
    void lootArms(Fighter *foe)
    {
        if(this==foe||life<=0) return;
        foe->purgeArms();
        foe->arrangeArms(0);
        purgeArms();
        arrangeArms(1);
        int id;
        int tot=countArms();
        id=0;
        for(int i=tot;i<10;i++) arms[i]=foe->arms[id++];
        arrangeArms(1);
    }
    WeaponBase* selectWeapon()
    {
        WeaponBase *sel=arms[currentWeapon];
        if(sel&&sel->isUsable())
        {
            currentWeapon=(currentWeapon+1)%10;
            return sel;
        }
        else
        {
            int idx=(currentWeapon+1)%10;
            while(idx!=currentWeapon)
            {
                sel=arms[idx];
                if(sel&&sel->isUsable())
                {
                    currentWeapon=(idx+1)%10;
                    return sel;
                }
                idx=(idx+1)%10;
            }
        }
        return nullptr;
    }
    void attackEnemy(Fighter *foe)
    {
        WeaponBase *wp=selectWeapon();
        if(wp==nullptr) return;
        wp->strike(this,foe);
    }
};

class DragonFighter:public Fighter
{
public:
    DragonFighter(const Fighter &f):Fighter(f){}
    void yell()
    {
        printf("%s %s %s %d yelled in city %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,pos);
    }
};

class LionFighter:public Fighter
{
public:
    int loyalty;
    LionFighter(const Fighter&f,int loyal):Fighter(f),loyalty(loyal){}
    virtual void advance();
    bool runAway()
    {
        bool bigger=(loyalty>0);
        switch(bigger)
        {
            case 1:
            return false;
            case 0:
            cout<<getTime()<<" "<<team<<" lion "<<fighterId<<" ran away"<<endl;
            return true;
        }
    }
};

class IcemanFighter:public Fighter
{
public:
    IcemanFighter(const Fighter &f):Fighter(f){}
    virtual void advance()
    {
        int d=0;
        if(team=="red") d=1;
        else d=-1;
        pos+=d;
        int loss=life/10;
        life-=loss;
        cout<<getTime()<<" "<<team<<" "<<type<<" "<<fighterId<<" marched to city "<<pos<<" with "<<life<<" elements and force "<<attack<<endl;
    }
};

class WolfFighter:public Fighter
{
public:
    WolfFighter(const Fighter &f):Fighter(f){}
    void stealArms(Fighter *foe)
    {
        if(foe->type[0]=='w'||foe==this) return;
        foe->purgeArms();
        foe->arrangeArms(0);
        purgeArms();
        arrangeArms(1);
        WeaponBase *firstArm=foe->arms[0];
        if(!firstArm) return;
        string wName=firstArm->weaponName;
        int selfCnt=countArms(),foeIdx=0;
        for(auto wp:foe->arms)
        {
            if(!wp||wp->weaponName!=wName) break;
            arms[selfCnt++]=wp;
            foe->arms[foeIdx++]=nullptr;
        }
        foe->arrangeArms(0);
        arrangeArms(1);
        printf("%s %s %s %d took %d %s from %s %s %d in city %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,foeIdx,wName.c_str(),foe->team.c_str(),foe->type.c_str(),foe->fighterId, pos);
    }
};

class NinjaFighter:public Fighter
{
public:
    NinjaFighter(const Fighter&f):Fighter(f){}
};


class SwordWeapon:public WeaponBase
{
public:
    SwordWeapon(const string &name_):WeaponBase(name_){}
    virtual void strike(Fighter *attacker,Fighter *victim)
    {
        victim->life-=(attacker->attack*2)/10;
    }
    virtual bool isUsable()
    {
        return true;
    }
};

class BombWeapon:public WeaponBase
{
public:
    bool active;
    BombWeapon(const string &name_):WeaponBase(name_),active(true) {}
    virtual void strike(Fighter *attacker,Fighter *victim)
    {
        if(!active) return;
        attacker->life-=(attacker->type=="ninja")?0:(attacker->attack*4)/20;
        victim->life-=(attacker->attack*4)/10;
        active=false;
    }
    virtual bool isUsable()
    {
        return active;
    }
};

class ArrowWeapon:public WeaponBase
{
public:
    int uses;
    ArrowWeapon(const string &name_,int useCount):WeaponBase(name_),uses(useCount){}
    virtual void strike(Fighter *attacker,Fighter *victim)
    {
        if(uses>=2) return;
        uses++;
        victim->life-=(attacker->attack*3)/10;
    }
    virtual bool isUsable()
    {
        return uses<2;
    }
};
SwordWeapon *globalSword=nullptr;
void Fighter::arrangeArms(bool useUsedFirst)
{
    int freshArrowCount=0;
    int usedArrowCount=0;
    int swordCount=0;
    int bombCount=0;
    for(int i=0;i<10;i++)
    {
        WeaponBase *wp=arms[i];
        if(!wp) continue;
        BombWeapon *bp;
        ArrowWeapon *ap;
        switch(wp->weaponName[0])
        {
            case 's':
            swordCount++;
            break;
            case 'b':
            bp=dynamic_cast<BombWeapon*>(wp);
            if(bp->isUsable()) bombCount++;
            delete wp;
            break;
            default:
            ap=dynamic_cast<ArrowWeapon*>(wp);
            if(ap->uses==1) usedArrowCount++;
            else if(ap->uses==0) freshArrowCount++;
            delete wp;
            break;
        }
        arms[i]=nullptr;
    }
    int idx=0;
    currentWeapon=0;
    while(swordCount--) arms[idx++]=globalSword;
    while(bombCount--) arms[idx++]=new BombWeapon("bomb");
    if(!useUsedFirst)
    {
        while(freshArrowCount--) arms[idx++]=new ArrowWeapon("arrow",0);
        while(usedArrowCount--) arms[idx++]=new ArrowWeapon("arrow",1);
    }
    else
    {
        while(usedArrowCount--) arms[idx++]=new ArrowWeapon("arrow",1);
        while(freshArrowCount--) arms[idx++]=new ArrowWeapon("arrow",0);
    }
}
static int loyaltyDecay,timeLimit,cityCount;
void LionFighter::advance()
{
    int d=(team=="red")?1:-1;
    pos+=d;
    loyalty-=loyaltyDecay;
    cout<<getTime()<<" "<<team<<" "<<type<<" "<<fighterId<<" marched to city "<<pos<<" with "<<life<<" elements and force "<<attack<<endl;
}
class City
{
public:
    Fighter *redFighter;
    Fighter *blueFighter;
    City(Fighter *r=nullptr,Fighter *b=nullptr):redFighter(r),blueFighter(b){}
};
unordered_map<string,int>teamFighterCount;
unordered_map<string,int>fighterLifeCost;
unordered_map<string,int>fighterAttackPower;
unordered_map<string,vector<string>>fighterCreationOrder;
vector<City>cities;
vector<string> redOrder={"iceman","lion","wolf","ninja","dragon"};
vector<string> blueOrder={"lion","dragon","ninja","iceman","wolf"};
vector<string> weaponTypes={"sword","bomb","arrow"};
enum BattleOutcome{BOTH_DEAD,BOTH_ALIVE,BLUE_WIN,RED_WIN };

class Headquarters
{
public:
    static int redBuildIndex;
    static int blueBuildIndex;
    int currentLife;
    string team;
    Headquarters(const string &tm,int life):team(tm),currentLife(life){}
    Fighter* createFighter()
    {
        Fighter *newFighter=nullptr;
        int id=teamFighterCount[team]+1;
        int index=(team == "red")?redBuildIndex:blueBuildIndex;
        int position=(team=="red")?0:cityCount+1;
        int cost=fighterLifeCost[fighterCreationOrder[team][index]];
        if(cost<=currentLife)
        {
            teamFighterCount[team]++;
            currentLife-=cost;
            if(team=="blue") blueBuildIndex=(blueBuildIndex+1)%5;
            else redBuildIndex=(redBuildIndex+1)%5;
            newFighter=new Fighter(id,cost,team,fighterCreationOrder[team][index],position,fighterAttackPower[fighterCreationOrder[team][index]]);
        }
        return newFighter;
    }
    WeaponBase* createWeapon(const string &wname)
    {
        if(wname=="sword") return globalSword;
        else if(wname=="bomb") return new BombWeapon(wname);
        else if(wname=="arrow") return new ArrowWeapon(wname,0);
        return nullptr;
    }
    Fighter* postProcessFighter(Fighter *f)
    {
        if(f==nullptr) return nullptr;
        Fighter *processed=nullptr;
        string tp=f->type;
        string wname=weaponTypes[f->fighterId%3];
        string wname2=weaponTypes[(f->fighterId+1)%3];
        switch(tp[0])
        {
            case 'd':
            f->arms[0]=createWeapon(wname);
            processed=new DragonFighter(*f);
            break;
            case 'n':
            f->arms[0]=createWeapon(wname);
            f->arms[1]=createWeapon(wname2);
            processed=new NinjaFighter(*f);
            break;
            case 'i':
            f->arms[0]=createWeapon(wname);
            processed=new IcemanFighter(*f);
            break;
            case 'l':
            f->arms[0]=createWeapon(wname);
            processed=new LionFighter(*f,currentLife);
            break;
            case 'w':
            processed=new WolfFighter(*f);
            break;
        }
        return processed;
    }
    void spawnFighters()
    {
        Fighter *f=postProcessFighter(createFighter());
        if(f)
        {
            printf("%s %s %s %d born\n",getTime().c_str(),f->team.c_str(),f->type.c_str(),f->fighterId);
            if(f->type=="lion")
            {
                LionFighter *lf=dynamic_cast<LionFighter*>(f);
                printf("Its loyalty is %d\n",lf->loyalty);
            }
            if(f->team=="red") cities[0].redFighter=f;
            else cities[cities.size()-1].blueFighter=f;
        }
    }
};


int Headquarters::redBuildIndex=0;
int Headquarters::blueBuildIndex=0;

inline static void lionEscape()
{
    for(int i=0;i<cities.size();i++)
    {
        if(cities[i].blueFighter!=nullptr&&cities[i].blueFighter->type=="lion")
        {
            LionFighter *lf=dynamic_cast<LionFighter*>(cities[i].blueFighter);
            if(lf->runAway())
            {
                delete cities[i].blueFighter;
                cities[i].blueFighter=nullptr;
            }
        }
        if(cities[i].redFighter!=nullptr&&cities[i].redFighter->type=="lion")
        {
            LionFighter *lf=dynamic_cast<LionFighter*>(cities[i].redFighter);
            if(lf->runAway())
            {
                delete cities[i].redFighter;
                cities[i].redFighter=nullptr;
            }
        }
    }
}

inline static void marchFighters()
{
    Fighter *blueF=cities[1].blueFighter;
    if(blueF)
    {
        blueF->captureHQ();
        delete cities[1].blueFighter;
        cities[1].blueFighter=nullptr;
    }
    Fighter *nextRed=cities[0].redFighter;
    cities[0].redFighter=nullptr;
    for(int i=1;i<cities.size()-1;i++)
    {
        Fighter *r=nextRed;
        Fighter *b=cities[i+1].blueFighter;
        nextRed=cities[i].redFighter;
        if(r) r->advance();
        cities[i].redFighter=r;
        if(b) b->advance();
        cities[i].blueFighter=b;
    }
    cities[cities.size()-1].blueFighter=nullptr;
    if(nextRed)
    {
        nextRed->captureHQ();
        delete nextRed;
    }
    
}

inline static void wolfRob()
{
    for(int i=1;i<cities.size()-1;i++)
    {
        if(cities[i].redFighter==nullptr||cities[i].blueFighter==nullptr) continue;
        if(cities[i].redFighter->type[0]=='w')
        {
            WolfFighter *wf=dynamic_cast<WolfFighter*>(cities[i].redFighter);
            wf->stealArms(cities[i].blueFighter);
        }
        if(cities[i].blueFighter->type[0]=='w')
        {
            WolfFighter *wf=dynamic_cast<WolfFighter*>(cities[i].blueFighter);
            wf->stealArms(cities[i].redFighter);
        }
    }
}

inline static BattleOutcome conductBattle(Fighter *first,Fighter *second)
{
    int stalemate=0;
    while(first->life>0&&second->life>0)
    {
        int beforeFirst=first->life, beforeSecond=second->life;
        if(first->life>0) first->attackEnemy(second);
        if(second->life>0) second->attackEnemy(first);
        if(beforeFirst==first->life&&beforeSecond==second->life) stalemate++;
        if(stalemate>=12) return BOTH_ALIVE;
    }
    Fighter *survivor=first->life>0?first:second;
    if(survivor->life<=0) return BOTH_DEAD;
    else return (survivor->team=="red")?RED_WIN:BLUE_WIN;
}

inline static void warInCities()
{
    for(int i=1;i<cities.size()-1;i++)
    {
        if(cities[i].redFighter==nullptr||cities[i].blueFighter==nullptr) continue;
        cities[i].redFighter->purgeArms();
        cities[i].redFighter->arrangeArms(true);
        cities[i].blueFighter->purgeArms();
        cities[i].blueFighter->arrangeArms(true);
        BattleOutcome result=(i%2==0)?conductBattle(cities[i].blueFighter,cities[i].redFighter):result=conductBattle(cities[i].redFighter,cities[i].blueFighter);
        DragonFighter *blueDragon=dynamic_cast<DragonFighter*>(cities[i].blueFighter);
        DragonFighter *redDragon=dynamic_cast<DragonFighter*>(cities[i].redFighter);
        switch(result)
        {
            case BOTH_ALIVE:
            printf("%s both red %s %d and blue %s %d were alive in city %d\n",getTime().c_str(),cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,cities[i].redFighter->pos);
            if(redDragon!=nullptr) redDragon->yell();
            if(blueDragon!=nullptr) blueDragon->yell();
            break;
            case BOTH_DEAD:
            printf("%s both red %s %d and blue %s %d died in city %d\n",getTime().c_str(),cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,cities[i].redFighter->pos);
            break;
            case RED_WIN:
            cities[i].redFighter->lootArms(cities[i].blueFighter);
            printf("%s red %s %d killed blue %s %d in city %d remaining %d elements\n",getTime().c_str(),cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,cities[i].redFighter->pos,cities[i].redFighter->life);
            if(redDragon!=nullptr) redDragon->yell();
            break;
            case BLUE_WIN:
            cities[i].blueFighter->lootArms(cities[i].redFighter);
            printf("%s blue %s %d killed red %s %d in city %d remaining %d elements\n",getTime().c_str(),cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,cities[i].blueFighter->pos,cities[i].blueFighter->life);
            if(blueDragon!=nullptr) blueDragon->yell();
            break;
        }
        cities[i].redFighter->purgeArms();
        cities[i].redFighter->arrangeArms(true);
        cities[i].blueFighter->purgeArms();
        cities[i].blueFighter->arrangeArms(true);
        if(cities[i].redFighter->life<=0)
        {
            delete cities[i].redFighter;
            cities[i].redFighter=nullptr;
        }
        if(cities[i].blueFighter->life<=0)
        {
            delete cities[i].blueFighter;
            cities[i].blueFighter=nullptr;
        }
    }
}

inline static void reportFighterStatus()
{
    for(int i=1;i<cities.size()-1;i++)
    {
        if(cities[i].redFighter)
        {
            int swordNum=0,bombNum=0,arrowNum=0;
            cities[i].redFighter->purgeArms();
            cities[i].redFighter->arrangeArms(true);
            for(auto wp:cities[i].redFighter->arms)
            {
                if(wp==nullptr) continue;
                switch(wp->weaponName[0])
                {
                    case 's':
                    swordNum++;
                    break;
                    case 'b':
                    bombNum++;
                    break;
                    case 'a':
                    arrowNum++;
                    break;
                }
            }
            printf("%s %s %s %d has %d sword %d bomb %d arrow and %d elements\n",getTime().c_str(),cities[i].redFighter->team.c_str(),cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,swordNum,bombNum,arrowNum,cities[i].redFighter->life);
        }
        if(cities[i].blueFighter!=nullptr)
        {
            int swordNum=0,bombNum=0,arrowNum=0;
            cities[i].blueFighter->purgeArms();
            cities[i].blueFighter->arrangeArms(true);
            for(auto wp:cities[i].blueFighter->arms)
            {
                if(wp==nullptr) continue;
                switch(wp->weaponName[0])
                {
                    case 's':
                    swordNum++;
                    break;
                    case 'b':
                    bombNum++;
                    break;
                    case 'a':
                    arrowNum++;
                    break;
                }
            }
            printf("%s %s %s %d has %d sword %d bomb %d arrow and %d elements\n",getTime().c_str(),cities[i].blueFighter->team.c_str(),cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,swordNum,bombNum,arrowNum,cities[i].blueFighter->life);
        }
    }
}

int main()
{
    int totalCases;
    cin>>totalCases;
    for(int caseNum=1;caseNum<=totalCases;caseNum++)
    {
        cout<<"Case "<<caseNum<<":"<<endl;
        int totLife;
        scanf("%d %d %d %d",&totLife,&cityCount,&loyaltyDecay,&timeLimit);
        scanf("%d %d %d %d %d",&fighterLifeCost["dragon"],&fighterLifeCost["ninja"],&fighterLifeCost["iceman"],&fighterLifeCost["lion"],&fighterLifeCost["wolf"]);
        scanf("%d %d %d %d %d",&fighterAttackPower["dragon"],&fighterAttackPower["ninja"],&fighterAttackPower["iceman"],&fighterAttackPower["lion"],&fighterAttackPower["wolf"]);
        for(City &ct:cities)
        {
            if(ct.redFighter!=nullptr) delete ct.redFighter;
            if(ct.blueFighter!=nullptr) delete ct.blueFighter;
        }
        cities.clear();
        if(globalSword==nullptr) globalSword=new SwordWeapon("sword");
        for(int i=0;i<cityCount+2;i++) cities.push_back(City(nullptr, nullptr));
        teamFighterCount["blue"]=0;
        blueConquered=false;
        Headquarters::blueBuildIndex=0;
        fighterCreationOrder["blue"]=blueOrder;
        teamFighterCount["red"]=0;
        redConquered=false;
        Headquarters::redBuildIndex=0;
        fighterCreationOrder["red"]=redOrder;
        currentTime=0;
        Headquarters redHQ("red",totLife);
        Headquarters blueHQ("blue",totLife);
        while(currentTime<=timeLimit&&(!blueConquered&&!redConquered))
        {
            int mod=currentTime%60;
            switch(mod)
            {
                case 0:
                redHQ.spawnFighters();
                blueHQ.spawnFighters();
                break;
                case 5:
                lionEscape();
                break;
                case 10:
                marchFighters();
                break;
                case 35:
                wolfRob();
                break;
                case 40:
                warInCities();
                break;
                case 50:
                printf("%s %d elements in %s headquarter\n",getTime().c_str(),redHQ.currentLife,redHQ.team.c_str());
                printf("%s %d elements in %s headquarter\n",getTime().c_str(),blueHQ.currentLife,blueHQ.team.c_str());
                break;
                case 55:
                reportFighterStatus();
                break;
            }
            currentTime+=5;
        }
    }
    return 0;
}
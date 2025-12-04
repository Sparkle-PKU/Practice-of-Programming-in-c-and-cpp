/*魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为1,2,3 .... N ( N <= 20 )。
红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。
两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。
双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。
武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），则武士死亡（消失）。
有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。
武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。
每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。
被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。反击可能致敌人于死地。
如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。
当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。
如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。
注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。
对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。
如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。
城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。
在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。
当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；
但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。
旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。
各种武器有其特点：
sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。
但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。
sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.
arrow有一个攻击力值R。如果下一步要走到的城市有敌人，那么拥有arrow的武士就会放箭攻击下一个城市的敌人（不能攻击对方司令部里的敌人）而不被还击。
arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。arrow使用3次后即被耗尽，武士失去arrow。两个相邻的武士可能同时放箭把对方射死。
拥有bomb的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，而且假设武士可以知道敌人的攻击力和生命值），那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。
武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。
不同的武士有不同的特点。
dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。
dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。士气增减发生在欢呼之前。
ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。
iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。
但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。
lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每经过一场未能杀死敌人的战斗，忠诚度就降低K。
忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。
Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓“战斗前”，就是每个小时的40分前的一瞬间。
wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。
被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。
以下是不同时间会发生的不同事件：
在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
制造武士需要生命元。
制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。
如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。
在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。
在每个小时的第10分：所有武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。
在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。
在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。
在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。
注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。
在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。
在每个小时的第40分：在有两个武士的城市，会发生战斗。 
如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事件发生，但战斗胜利后应该发生的事情都会发生。
如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。
在每个小时的第50分，司令部报告它拥有的生命元数量。
在每个小时的第55分，每个武士报告其拥有的武器情况。
武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。
任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。
任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。
给定一个时间，要求你将从0点0分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：
1) 武士降生
输出样例： 000:00 blue lion 1 born
表示在 0点0分，编号为1的蓝魔lion武士降生
如果造出的是dragon，那么还要多输出一行，例：
000:00 blue dragon 1 born
Its morale is 23.34
表示该该dragon降生时士气是23. 34(四舍五入到小数点后两位)
如果造出的是lion，那么还要多输出一行，例:
000:00 blue lion 1 born
Its loyalty is 24
表示该lion降生时的忠诚度是24
2) lion逃跑
输出样例： 000:05 blue lion 1 ran away 
表示在 0点5分，编号为1的蓝魔lion武士逃走
3) 武士前进到某一城市
输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
表示在 0点10分，红魔1号武士iceman前进到1号城市，此时他生命值为20,攻击力为30
对于iceman,输出的生命值和攻击力应该是变化后的数值
4)武士放箭
输出样例： 000:35 blue dragon 1 shot
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
000:35 blue dragon 1 shot and killed red lion 4
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。
5)武士使用bomb
输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。
6) 武士主动进攻
输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
表示在0点40分，1号城市中，红魔1号武士iceman 进攻蓝魔1号武士lion,在发起进攻前，红魔1号武士iceman生命值为20，攻击力为 30
7) 武士反击
输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1 
表示在1点40分，1号城市中，蓝魔2号武士dragon反击红魔2号武士lion
8) 武士战死
输出样例：001:40 red lion 2 was killed in city 1
被箭射死的武士就不会有这一条输出。
9) 武士欢呼
输出样例：003:40 blue dragon 2 yelled in city 4
10) 武士获取生命元( elements )
输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter
输出不包括在30分不是通过战斗获取的elements
11) 旗帜升起
输出样例：004:40 blue flag raised in city 4
12) 武士抵达敌军司令部
输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
(此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值
13) 司令部被占领
输出样例：003:10 blue headquarter was taken
14)司令部报告生命元数量
000:50 100 elements in red headquarter 
000:50 120 elements in blue headquarter
表示在0点50分，红方司令部有100个生命元，蓝方有120个
15)武士报告武器情况
000:55 blue wolf 2 has arrow(2),bomb,sword(23)
000:55 blue wolf 4 has no weapon
000:55 blue wolf 5 has sword(20)
表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。
蓝魔4号武士wolf没武器。
蓝魔5号武士wolf有一支攻击力为20的sword。
交代武器情况时，次序依次是：arrow,bomb,sword。
如果没有某种武器，某种武器就不用提。报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。
输出事件时：
首先按时间顺序输出；
同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。
在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些事件，序号小的应该先输出。
两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。
显然，13号事件发生之前的一瞬间一定发生了12号事件。输出时，这两件事算同一时间发生，但是应先输出12号事件
虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

输入第一行是t,代表测试数据组数
每组样例共三行。
第一行，五个整数 M,N,R,K, T。其含义为：
每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000
第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000
第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000

对每组数据，先输出一行：
Case n:
如对第一组数据就输出 Case1:
然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时: 分”，“时”有三位，“分”有两位。*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

static int currentTime=0;
static bool redConquered=false;
static bool blueConquered=false;
unordered_map<string,int>teamFighterCount;
unordered_map<string,int>fighterLifeCost;
unordered_map<string,int>fighterAttackPower;
unordered_map<string,vector<string>>fighterCreationOrder;
vector<string> redOrder={"iceman","lion","wolf","ninja","dragon"};
vector<string> blueOrder={"lion","dragon","ninja","iceman","wolf"};
vector<string> weaponTypes={"sword","bomb","arrow"};
enum BattleOutcome{BOTH_DEAD,BOTH_ALIVE,BLUE_WIN,RED_WIN };
static int loyaltyDecay,timeLimit,cityCount;
class ArrowWeapon;
class SwordWeapon;

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
    vector<WeaponBase*>arms;
    bool hasReachedHQ;
    Fighter(int id,int initLife,const string &tm,const string &tp,int position,int atk):fighterId(id),life(initLife),attack(atk),team(tm),type(tp),pos(position),currentWeapon(0),hasReachedHQ(false)
    {
        arms=vector<WeaponBase*>(10,nullptr);
    }
    ~Fighter()
    {
        for(auto &w:arms)
        {
            if(w)
            {
                delete w;
                w=nullptr;
            }
        }
    }
    Fighter(const Fighter&f)
    {
        type=f.type;
        team=f.team;
        pos=f.pos;
        life=f.life;
        fighterId=f.fighterId;
        attack=f.attack;
        arms=std::move(f.arms);
    }
    virtual void advance(void)
    {
        if(hasReachedHQ) return; 
        int dir=(team=="red")?1:-1;
        pos+=dir;
        if((team=="red"&&pos==cityCount+1)||(team=="blue"&&pos==0))
        {
            hasReachedHQ=true;
            printf("%s %s %s %d reached %s headquarter with %d elements and force %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,(team=="red" ? "blue":"red"),life,attack);
        }
        else printf("%s %s %s %d marched to city %d with %d elements and force %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,pos,life,attack);
    }
    void arrangeArms(bool useUsedFirst);
    int countArms(void)
    {
        int count=0;
        for(auto wp:arms)
        {
            if(wp!=nullptr) count++;
            else break;
        }
        return count;
    }
    void purgeArms(void)
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
        for(int i=tot;i<10;i++)
        {
            arms[i]=foe->arms[id++];
        }
        arrangeArms(1);
    }
    ArrowWeapon* getArrow(void);
    bool hasUsableBomb(void)
    {
        for(auto wp:arms)
        {
            if(wp&&wp->weaponName=="bomb"&&wp->isUsable()) return true;
        }
        return false;
    }
    
    void useBomb(Fighter *victim)
    {
        for(auto& wp:arms)
        {
            if(wp&&wp->weaponName=="bomb"&&wp->isUsable())
            {
                wp->strike(this,victim);
                if(victim->life<=0)
                {
                    victim->life=0;
                    if(victim) delete victim;
                }
                break;
            }
        }
    }

    SwordWeapon* getUsableSword(void);
    void attackEnemy(Fighter* foe);
    void reportWeapons(void);
};

class DragonFighter:public Fighter
{
public:
    double morale;
    DragonFighter(const Fighter &f,int currentLife):Fighter(f)
    {
        morale=((double)currentLife)/((double)fighterLifeCost["dragon"]);
    }
    void yell(void)
    {
        printf("%s %s %s %d yelled in city %d\n",getTime().c_str(),team.c_str(),type.c_str(),fighterId,pos);
    }
};

class LionFighter:public Fighter
{
public:
    int loyalty;
    LionFighter(const Fighter&f,int loyal):Fighter(f),loyalty(loyal){}
    virtual void advance(void);
    bool runAway(void)
    {
        int enemyHQ=(team=="red")?cityCount+1:0;
        if(pos==enemyHQ) return false;
        if(loyalty<=0)
        {
            cout<<getTime()<<" "<<team<<" lion "<<fighterId<<" ran away"<<endl;
            return true;
        }
        return false;
    }
};

class IcemanFighter:public Fighter
{
public:
    int steps=0;
    IcemanFighter(const Fighter &f):Fighter(f){}
    virtual void advance(void)
    {
        int d=(team=="red")?1:-1;
        pos+=d;
        steps++;
        if(steps%2==0)
        {
            if(life>9) life-=9;
            else life=1;
            attack+=20;
        }
        cout<<getTime()<<" "<<team<<" "<<type<<" "<<fighterId<<" marched to city "<<pos<<" with "<<life<<" elements and force "<<attack<<endl;
    }
};

class WolfFighter:public Fighter
{
public:
    WolfFighter(const Fighter &f):Fighter(f){}
    void stealArms(Fighter* foe)
    {
        if (!foe||foe==this||life<=0) return;
        foe->purgeArms();           
        foe->arrangeArms(false);    
        purgeArms();                
        arrangeArms(true);
        int selfCnt=countArms(),taken=0;
        for(int i=0;i<10&&foe->arms[i];i++)
        {
            if(selfCnt==10) break;
            arms[selfCnt++]=foe->arms[i];
            foe->arms[i]=nullptr;
            taken++;
        }
        foe->arrangeArms(false);
        arrangeArms(true);
    
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
    int dmg;
    SwordWeapon(int base):WeaponBase("sword"),dmg(base/5){}
    void strike(Fighter*,Fighter* victim)
    {
        if(dmg<=0) return;
        victim->life-=dmg;
        dmg*=0.8;
    }
    bool isUsable()
    {
        return dmg>0;
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
    static int power;
    ArrowWeapon(const string &name_,int useCount):WeaponBase(name_),uses(useCount){}
    virtual void strike(Fighter *attacker,Fighter *victim)
    {
        if(uses>=3||victim==nullptr||victim->life<=0) return;
        uses++;
        victim->life-=power;
        if(victim->life<0) victim->life=0;
    }
    virtual bool isUsable()
    {
        return uses<3;
    }
};

ArrowWeapon* Fighter::getArrow(void)
{
    for(auto wp:arms)
    {
        if(!wp) continue;
        if(wp->weaponName=="arrow")
        {
            ArrowWeapon* ap=dynamic_cast<ArrowWeapon*>(wp);
            if(ap&&ap->isUsable()) return ap;
        }
    }
    return nullptr;
}

void Fighter::reportWeapons(void)
{
    bool first=true;
    auto prefix=[&]()
    {
        if(first)
        {
            printf("%s %s %s %d has ",getTime().c_str(),team.c_str(),type.c_str(),fighterId);
            first=false;
        }
        else printf(",");
    };
    for(auto wp:arms)
    {
        if(wp&&wp->weaponName=="arrow"&&wp->isUsable())
        {
            prefix();
            auto* ap=static_cast<ArrowWeapon*>(wp);
            printf("arrow(%d)",3-ap->uses);
            break;
        }
    }
    for(auto wp:arms)
    {
        if(wp&&wp->weaponName=="bomb"&&wp->isUsable())
        {
            prefix();
            printf("bomb");
            break;
        }
    }
    for(auto wp:arms)
    {
        if(wp&&wp->weaponName=="sword"&&wp->isUsable())
        {
            prefix();
            auto* sw=static_cast<SwordWeapon*>(wp);
            printf("sword(%d)",sw->dmg);
            break;
        }
    }
    if(first) printf("%s %s %s %d has no weapon",getTime().c_str(),team.c_str(),type.c_str(),fighterId);
    puts("");
}

int ArrowWeapon::power=0;

void Fighter::arrangeArms(bool useUsedFirst)
{
    vector<WeaponBase*> keep;
    keep.reserve(10);
    for(auto wp:arms)
    {
        if(wp&&wp->weaponName=="sword"&&wp->isUsable()) keep.push_back(wp);
    }
    vector<WeaponBase*>bombs,freshAr,usedAr;
    for(auto wp:arms)
    {
        if(!wp||wp->weaponName=="sword") continue;
        if(wp&&wp->weaponName=="bomb"&&wp->isUsable()) bombs.push_back(wp);
        else if(wp->weaponName=="arrow")
        {
            auto* ap=static_cast<ArrowWeapon*>(wp);
            (ap->uses==0?freshAr:usedAr).push_back(wp);
        }
        else delete wp;
    }
    arms.assign(10,nullptr);
    int p=0;
    for(auto w:keep)
    {
        arms[p++]=w;
    }
    for(auto w:bombs)
    {
        arms[p++]=w;
    }
    auto& A1=useUsedFirst?usedAr:freshAr;
    auto& A2=useUsedFirst?freshAr:usedAr;
    for(auto w:A1)
    {
        arms[p++]=w;
    }
    for(auto w:A2)
    {
        arms[p++]=w;
    }
    currentWeapon=0;
}

void LionFighter::advance()
{
    int d=(team=="red")?1:-1;
    pos+=d;
    cout<<getTime()<<" "<<team<<" "<<type<<" "<<fighterId<<" marched to city "<<pos<<" with "<<life<<" elements and force "<<attack<<endl;
}
class City
{
public:
    int elements;
    int flag;
    int consecutiveWin;
    Fighter *redFighter;
    Fighter *blueFighter;
    City(Fighter *r=nullptr,Fighter *b=nullptr):redFighter(r),blueFighter(b),elements(0),flag(0),consecutiveWin(0){}
};

vector<City>cities;

class Headquarters
{
public:
    static int redBuildIndex;
    static int blueBuildIndex;
    int currentLife;
    int enemyCnt;
    string team;
    bool waiting;
    Headquarters(const string &tm,int life):team(tm),currentLife(life),waiting(false),enemyCnt(0){}
    Fighter* createFighter(void)
    {
        int index=(team=="red")?redBuildIndex:blueBuildIndex;
        int cost=fighterLifeCost[fighterCreationOrder[team][index]];
        if(cost>currentLife) return nullptr;
        teamFighterCount[team]++;
        currentLife-=cost;
        if (team=="blue") blueBuildIndex=(blueBuildIndex+1)%5;
        else redBuildIndex=(redBuildIndex+1)%5;
        int id=teamFighterCount[team];
        int position=(team=="red")?0:cityCount+1;
        string type=fighterCreationOrder[team][index];
        return new Fighter(id,cost,team,type,position,fighterAttackPower[type]);
    }
    WeaponBase* createWeapon(const string &wname,Fighter *f)
    {
        if(wname=="sword") return new SwordWeapon(f->attack);
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
            f->arms[0]=createWeapon(wname,f);
            processed=new DragonFighter(*f,currentLife);
            break;
            case 'n':
            f->arms[0]=createWeapon(wname,f);
            f->arms[1]=createWeapon(wname2,f);
            processed=new NinjaFighter(*f);
            break;
            case 'i':
            f->arms[0]=createWeapon(wname,f);
            processed=new IcemanFighter(*f);
            break;
            case 'l':
            processed=new LionFighter(*f,currentLife);
            break;
            case 'w':
            processed=new WolfFighter(*f);
            break;
        }
        return processed;
    }
    void spawnFighters(void)
    {
        Fighter* f=createFighter();
        if(!f)
        {
            waiting=true;
            return;
        }
        waiting=false;
        f=postProcessFighter(f);
        if(f)
        {
            printf("%s %s %s %d born\n",getTime().c_str(),f->team.c_str(),f->type.c_str(),f->fighterId);
            if(f->type=="lion")
            {
                LionFighter *lf=dynamic_cast<LionFighter*>(f);
                printf("Its loyalty is %d\n",lf->loyalty);
            }
            else if(f->type=="dragon")
            {
                DragonFighter *df=dynamic_cast<DragonFighter*>(f);
                printf("Its morale is %.2lf\n",df->morale);
            }
            if(f->team=="red") cities[0].redFighter=f;
            else cities[cities.size()-1].blueFighter=f;
        }
    }
};

int Headquarters::redBuildIndex=0;
int Headquarters::blueBuildIndex=0;

inline static void lionEscape(void)
{
    for(int i=0;i<=cityCount;i++)
    {
        if(cities[i].redFighter!=nullptr&&cities[i].redFighter->type=="lion")
        {
            LionFighter *lf=dynamic_cast<LionFighter*>(cities[i].redFighter);
            if(lf&&lf->runAway())
            {
                delete cities[i].redFighter;
                cities[i].redFighter=nullptr;
            }
        }
    }
    for(int i=cityCount+1;i>0;i--)
    {
        if(cities[i].blueFighter!=nullptr&&cities[i].blueFighter->type=="lion")
        {
            LionFighter *lf=dynamic_cast<LionFighter*>(cities[i].blueFighter);
            if(lf&&lf->runAway())
            {
                delete cities[i].blueFighter;
                cities[i].blueFighter=nullptr;
            }
        }
    }
}
void marchFighters(Headquarters& redHQ,Headquarters& blueHQ)
{
    for(int i=0;i<=cityCount+1;i++)
    {
        if(cities[i].redFighter&&cities[i].redFighter->life<=0)
        {
            delete cities[i].redFighter;
            cities[i].redFighter=nullptr;
        }
        if(cities[i].blueFighter&&cities[i].blueFighter->life<=0)
        {
            delete cities[i].blueFighter;
            cities[i].blueFighter=nullptr;
        }
    }
    Fighter* blueInRedHQ=cities[0].blueFighter;
    Fighter* redInBlueHQ=cities[cityCount+1].redFighter;
    vector<Fighter*>nxtRed(cityCount+2,nullptr);
    vector<Fighter*>nxtBlue(cityCount+2,nullptr);
    for(int i=0;i<=cityCount;i++)
    {
        if(cities[i].redFighter)  nxtRed[i+1]=cities[i].redFighter;
    }
    for(int i=cityCount+1;i>=1;i--)
    {
        if(cities[i].blueFighter) nxtBlue[i-1]=cities[i].blueFighter;
    }
    for(int i=0;i<=cityCount+1;i++)
    {
        cities[i].redFighter=nullptr;
        cities[i].blueFighter=nullptr;
    }
    if(blueInRedHQ) cities[0].blueFighter=blueInRedHQ;
    if(redInBlueHQ) cities[cityCount+1].redFighter=redInBlueHQ;
    struct Event
    {
        int pos;
        long long seq;
        string text;
    };
    vector<Event>todo;
    static long long seqGen=0;
    auto icemanStep=[](Fighter*f)
    {
        if(f&&f->type=="iceman")
        {
            auto* ic=static_cast<IcemanFighter*>(f);
            if(++ic->steps%2==0)
            {
                ic->life=ic->life>9?ic->life-9:1;
                ic->attack+=20;
            }
        }
    };
    for(int pos=0;pos<=cityCount+1;pos++)
    {
        if(auto* r=nxtRed[pos])
        {
            icemanStep(r);
            r->pos=pos;
            ostringstream oss;
            if(pos==cityCount+1)
            {
                oss<<getTime()<<" red "<<r->type<<' '<<r->fighterId<<" reached blue headquarter with "<<r->life<<" elements and force "<<r->attack;
                todo.push_back({pos,seqGen++,oss.str()});
                if(++redHQ.enemyCnt==2)
                {
                    todo.push_back({pos,seqGen++,getTime()+" blue headquarter was taken"});
                    blueConquered=true;
                }
                if(!cities[pos].redFighter) cities[pos].redFighter=r;
            }
            else if(pos!=0)
            {
                oss<<getTime()<<" red "<<r->type<<' '<<r->fighterId<<" marched to city "<<pos<<" with "<<r->life<<" elements and force "<<r->attack;
                todo.push_back({pos,seqGen++,oss.str()});
                cities[pos].redFighter=r;
            }
        }
    }
    for(int pos=0;pos<=cityCount+1;pos++)
    {
        if(auto* b=nxtBlue[pos])
        {
            icemanStep(b);
            b->pos=pos;
            ostringstream oss;
            if(pos==0)
            {
                oss<<getTime()<<" blue "<<b->type<<' '<<b->fighterId<<" reached red headquarter with "<< b->life<<" elements and force "<<b->attack;
                todo.push_back({pos,seqGen++,oss.str()});
                if(++blueHQ.enemyCnt==2)
                {
                    todo.push_back({pos,seqGen++,getTime()+" red headquarter was taken"});
                    redConquered=true;
                }
                if(!cities[pos].blueFighter) cities[pos].blueFighter=b;
            }
            else if(pos!=cityCount+1)
            {
                oss<<getTime()<<" blue "<<b->type<<' '<<b->fighterId<<" marched to city "<<pos<<" with "<<b->life<<" elements and force "<<b->attack;
                todo.push_back({pos,seqGen++,oss.str()});
                cities[pos].blueFighter=b;
            }
        }
    }
    stable_sort(todo.begin(),todo.end(),[](const Event& a,const Event& b){return(a.pos<b.pos)||(a.pos==b.pos&&a.seq<b.seq);});
    for(auto& ev:todo)
    {
        puts(ev.text.c_str());
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

static void rewardWinner(Fighter* win,Headquarters& hq)
{
    if(!win) return;
    if(hq.currentLife>=8)
    {
        hq.currentLife-=8;
        win->life+=8;
    }
}

static void harvestElements(int idx,Fighter* win,Headquarters& hq)
{
    if(cities[idx].elements==0) return;
    hq.currentLife+=cities[idx].elements;
    printf("%s %s %s %d earned %d elements for his headquarter\n",getTime().c_str(),win->team.c_str(),win->type.c_str(),win->fighterId,cities[idx].elements);
    cities[idx].elements=0;
}

void Fighter::attackEnemy(Fighter* foe)
{
    if(!foe||life<=0) return;
    int dmg=attack;
    if(auto* sw=getUsableSword()) sw->strike(this,foe);
    foe->life-=dmg;
    if(foe->life<0) foe->life=0;
}

void counterAttack(Fighter* self,Fighter* foe)
{
    if(self->attack>0) foe->life-=self->attack/2;
    if(foe->life<0) foe->life=0;
    for(auto wp:self->arms)
        if(auto* sw=dynamic_cast<SwordWeapon*>(wp);sw&&sw->isUsable())
        {
            sw->strike(self,foe);
            break;
        }
}

SwordWeapon* Fighter::getUsableSword()
{
    for(auto wp:arms)
    {
        if(auto sw=dynamic_cast<SwordWeapon*>(wp);sw&&sw->isUsable()) return sw;
    }
    return nullptr;
}

void warInCities(Headquarters&redHQ,Headquarters&blueHQ)
{
    vector<pair<int,Fighter*>> rewardRed,rewardBlue;
    auto cmpDist=[](auto &a,auto &b){return a.first<b.first;};
    for(int i=1;i<=cityCount;i++)
    {
        Fighter *red=cities[i].redFighter;
        Fighter *blue=cities[i].blueFighter;
        if (!red||!blue) continue;
        bool redAlive=red->life>0;
        bool blueAlive=blue->life>0;
        bool normalBattle=(redAlive&&blueAlive);
        int preHP_red =red->life;
        int preHP_blue=blue->life;
        bool redFirst=(cities[i].flag==1)||(cities[i].flag==0&&i%2==1);
        Fighter *atk=redFirst?red:blue;
        Fighter *def=redFirst?blue:red;
        if(normalBattle)
        {
            printf("%s %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",getTime().c_str(),atk->team.c_str(),atk->type.c_str(),atk->fighterId,def->team.c_str(),def->type.c_str(),def->fighterId,i,atk->life,atk->attack);
            atk->attackEnemy(def);
            if(def->life<=0) printf("%s %s %s %d was killed in city %d\n",getTime().c_str(),def->team.c_str(),def->type.c_str(), def->fighterId,i);
            if(def->life>0&&atk->life>0&&def->type!="ninja")
            {
                printf("%s %s %s %d fought back against %s %s %d in city %d\n",getTime().c_str(),def->team.c_str(),def->type.c_str(),def->fighterId,atk->team.c_str(),atk->type.c_str(),atk->fighterId,i);
                counterAttack(def,atk);
                if(atk->life<=0) printf("%s %s %s %d was killed in city %d\n",getTime().c_str(),atk->team.c_str(),atk->type.c_str(),atk->fighterId,i);
                
            }
        }
        Fighter *winner=nullptr,*loser=nullptr;
        if(red->life>0&&blue->life<=0)
        {
            winner=red;
            loser= blue;
        }
        else if(blue->life>0&&red->life<=0)
        {
            winner=blue;
            loser=red;
        }
        if(winner)
        {
            if(winner->team=="red")
            {
                if(cities[i].consecutiveWin>=0) cities[i].consecutiveWin++;
                else cities[i].consecutiveWin=1;
            }
            else if(winner->team=="blue")
            {
                if(cities[i].consecutiveWin<=0) cities[i].consecutiveWin--;
                else cities[i].consecutiveWin=-1;
            }
            if(winner->type=="wolf")
            {
                WolfFighter* wf=dynamic_cast<WolfFighter*>(winner);
                wf->stealArms(loser);
            }
            if(loser->type=="lion") winner->life+=(loser==red?preHP_red:preHP_blue);
            if(winner->type=="dragon")
            {
                auto *df=static_cast<DragonFighter*>(winner);
                df->morale+=0.2;
                if(winner==atk&&df->morale>0.8) df->yell();
            }
            harvestElements(i,winner,winner->team=="red"?redHQ:blueHQ);
            if(abs(cities[i].consecutiveWin)==2)
            {
                int newFlag=cities[i].consecutiveWin>0?1:-1;
                if(cities[i].flag!=newFlag)
                {
                    cities[i].flag=newFlag;
                    printf("%s %s flag raised in city %d\n",getTime().c_str(),newFlag==1?"red":"blue",i);
                }
            }
            int dist=(winner->team=="red"?(cityCount+1-i):i);
            if(winner->team=="red") rewardRed.emplace_back(dist,winner);
            else rewardBlue.emplace_back(dist, winner);
        }
        else
        {
            if(red&&redAlive&&blue&&blueAlive)
            cities[i].consecutiveWin=0;
            else if(redAlive&&!blueAlive)
            {
                if(cities[i].consecutiveWin>=0) cities[i].consecutiveWin++;
                else cities[i].consecutiveWin=1;
            }
            else if(!redAlive&&blueAlive)
            {
                if(cities[i].consecutiveWin<=0) cities[i].consecutiveWin--;
                else cities[i].consecutiveWin=-1;
            }
            if(redAlive && red->type=="lion") dynamic_cast<LionFighter*>(red)->loyalty-=loyaltyDecay;
            if(blueAlive && blue->type=="lion") dynamic_cast<LionFighter*>(blue)->loyalty-=loyaltyDecay;
            if(redAlive&&atk==red&&red->type=="dragon")
            {
                DragonFighter* df=dynamic_cast<DragonFighter*>(red);
                df->morale-=0.2;
                if(df->morale>0.8) printf("%s %s dragon %d yelled in city %d\n",getTime().c_str(),df->team.c_str(),df->fighterId,i);
            }
            if(blueAlive&&atk==blue&&blue->type=="dragon")
            {
                DragonFighter* df=dynamic_cast<DragonFighter*>(blue);
                df->morale-=0.2;
                if(df->morale>0.8) printf("%s %s dragon %d yelled in city %d\n",getTime().c_str(),df->team.c_str(),df->fighterId,i);
            }
        }
        if(loser)
        {
            if(loser==red)
            {
                delete red;
                cities[i].redFighter=nullptr;
            }
            else
            {
                delete blue;
                cities[i].blueFighter=nullptr;
            }
        }
    }
    sort(rewardRed.begin(),rewardRed.end(),cmpDist);
    sort(rewardBlue.begin(),rewardBlue.end(),cmpDist);
    for(auto &p:rewardRed)
    {
        rewardWinner(p.second,redHQ);
    }
    for(auto &p:rewardBlue)
    {
        rewardWinner(p.second,blueHQ);
    }
}

inline static void reportFighterStatus(void)
{
    for(int i=0;i<=cityCount+1;i++)
    {
        if(cities[i].redFighter&&cities[i].redFighter->life<=0)
        {
            delete cities[i].redFighter;
            cities[i].redFighter=nullptr;
        }
        if(cities[i].blueFighter&&cities[i].blueFighter->life<=0)
        {
            delete cities[i].blueFighter;
            cities[i].blueFighter=nullptr;
        }
    }
    for(int i=0;i<=cityCount+1;i++)
    {
        if(cities[i].redFighter) cities[i].redFighter->reportWeapons();
    }
    for(int i=0;i<=cityCount+1;i++)
    {
        if(cities[i].blueFighter) cities[i].blueFighter->reportWeapons();
    }
}

inline void increaseCityElements(void)
{
    for(int i=1;i<=cityCount;i++)
    {
        cities[i].elements+=10;
    }
}

inline void takeawayCityElements(Headquarters& redHQ,Headquarters& blueHQ)
{
    for(int i=1;i<=cityCount;i++)
    {
        if(cities[i].elements==0) continue; 
        else if(cities[i].redFighter==nullptr&&cities[i].blueFighter!=nullptr)
        {
            blueHQ.currentLife+=cities[i].elements;
            printf("%s blue %s %d earned %d elements for his headquarter\n",getTime().c_str(),cities[i].blueFighter->type.c_str(),cities[i].blueFighter->fighterId,cities[i].elements);cities[i].elements=0;
        }
        else if(cities[i].redFighter!=nullptr&&cities[i].blueFighter==nullptr)
        {
            redHQ.currentLife+=cities[i].elements;
            printf("%s red %s %d earned %d elements for his headquarter\n",getTime().c_str(),cities[i].redFighter->type.c_str(),cities[i].redFighter->fighterId,cities[i].elements);
            cities[i].elements=0;
        }
    }
    return;
}

void releaseArrow(void)
{
    for(int i=1;i<=cityCount;i++)
    {
        if(auto* shooter=cities[i].redFighter)
        {
            auto* target=(i<cityCount)?cities[i+1].blueFighter:nullptr;
            if(auto* arrow=shooter->getArrow())
            {
                if(target&&target->life>0)
                {
                    arrow->strike(shooter,target);
                    if(target->life<=0) printf("%s red %s %d shot and killed blue %s %d\n",getTime().c_str(),shooter->type.c_str(),shooter->fighterId,target->type.c_str(),target->fighterId);
                    else printf("%s red %s %d shot\n",getTime().c_str(),shooter->type.c_str(),shooter->fighterId);
                }
            }
        }
        if(auto* shooter=cities[i].blueFighter)
        {
            auto* target=(i>1)?cities[i-1].redFighter:nullptr;
            if(auto* arrow=shooter->getArrow())
            {
                if(target&&target->life>0)
                {
                    arrow->strike(shooter,target);
                    if(target->life<=0) printf("%s blue %s %d shot and killed red %s %d\n",getTime().c_str(),shooter->type.c_str(), shooter->fighterId,target->type.c_str(),target->fighterId);
                    else printf("%s blue %s %d shot\n",getTime().c_str(),shooter->type.c_str(),shooter->fighterId);
                }
            }
        }
    }
}

inline bool willDie(Fighter* attacker,Fighter* defender,bool attack)
{
    if(attack)
    {
        if(defender->type=="ninja") return false;
        int atkPower=attacker->attack;
        for(auto wp:attacker->arms)
        {
            if (auto sw=dynamic_cast<SwordWeapon*>(wp);sw&&sw->isUsable())
            {
                if(sw->dmg>=0) atkPower+=sw->dmg;
                break;
            }
        }
        int defenderLifeAfterAttack=defender->life-atkPower;
        if(defenderLifeAfterAttack<=0) return false;
        int defPower=defender->attack/2;  
        for(auto wp:defender->arms)
        {
            if(auto sw=dynamic_cast<SwordWeapon*>(wp); sw && sw->isUsable())
            {
                if(sw->dmg>=0) defPower+=sw->dmg;
                break;
            }
        }
        int attackerLifeAfterCounter=attacker->life-defPower;
        return attackerLifeAfterCounter<=0;
    }
    else
    {
        int atkPower=attacker->attack;
        for(auto wp:attacker->arms)
        {
            if(auto sw=dynamic_cast<SwordWeapon*>(wp);sw&&sw->isUsable())
            {
                atkPower+=sw->dmg;
                break;
            }
        }
        int defenderLifeAfterAttack=defender->life-atkPower;
        return defenderLifeAfterAttack<=0; 
    }
}

inline void useBomb(void)
{
    for(int i=1;i<=cityCount;i++)
    {
        Fighter* red=cities[i].redFighter;
        Fighter* blue=cities[i].blueFighter;
        if(!red||!blue) continue;
        bool redFirst=(cities[i].flag==0&&i%2==1)||cities[i].flag==1;
        Fighter* attacker=redFirst?red:blue;
        Fighter* defender=redFirst?blue:red;
        if(attacker->life>0&&defender->life>0)
        {
            string defender_type=defender->type;
            int defender_id=defender->fighterId;
            string attacker_type=attacker->type;
            int attacker_id=attacker->fighterId;
            string defender_team=defender->team;
            string attacker_team=attacker->team;
            if(attacker->hasUsableBomb()&&willDie(attacker,defender,true))
            {
                attacker->useBomb(defender);
                printf("%s %s %s %d used a bomb and killed %s %s %d\n",getTime().c_str(),attacker_team.c_str(),attacker_type.c_str(),attacker_id,defender_team.c_str(),defender_type.c_str(),defender_id);
                delete attacker;
                cities[i].redFighter=nullptr;
                cities[i].blueFighter=nullptr;
                continue;
            }
            if(defender->hasUsableBomb()&&willDie(attacker,defender,false))
            {
                defender->useBomb(attacker);
                printf("%s %s %s %d used a bomb and killed %s %s %d\n",getTime().c_str(),defender_team.c_str(),defender_type.c_str(),defender_id,attacker_team.c_str(),attacker_type.c_str(),attacker_id);
                delete defender;
                cities[i].redFighter=nullptr; 
                cities[i].blueFighter=nullptr;
                continue;
            }
        }
    }
}

int main(void)
{
    int totalCases;
    cin>>totalCases;
    for(int caseNum=1;caseNum<=totalCases;caseNum++)
    {
        cout<<"Case "<<caseNum<<":"<<endl;
        int totLife;
        scanf("%d %d %d %d %d",&totLife,&cityCount,&ArrowWeapon::power,&loyaltyDecay,&timeLimit);
        scanf("%d %d %d %d %d",&fighterLifeCost["dragon"],&fighterLifeCost["ninja"],&fighterLifeCost["iceman"],&fighterLifeCost["lion"],&fighterLifeCost["wolf"]);
        scanf("%d %d %d %d %d",&fighterAttackPower["dragon"],&fighterAttackPower["ninja"],&fighterAttackPower["iceman"],&fighterAttackPower["lion"],&fighterAttackPower["wolf"]);
        for(City &ct:cities)
        {
            if(ct.redFighter!=nullptr) delete ct.redFighter;
            if(ct.blueFighter!=nullptr) delete ct.blueFighter;
        }
        cities.clear();
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
                marchFighters(redHQ,blueHQ);
                break;
                case 20:
                increaseCityElements();
                break;
                case 30:
                takeawayCityElements(redHQ,blueHQ);
                break;
                case 35:
                releaseArrow();
                break;
                case 38:
                useBomb();
                break;
                case 40:
                warInCities(redHQ,blueHQ);
                break;
                case 50:
                printf("%s %d elements in %s headquarter\n",getTime().c_str(),redHQ.currentLife,redHQ.team.c_str());
                printf("%s %d elements in %s headquarter\n",getTime().c_str(),blueHQ.currentLife,blueHQ.team.c_str());
                break;
                case 55:
                reportFighterStatus();
                break;
            }
            if(mod!=35&&mod!=38) currentTime+=5;
            else if(mod==35) currentTime+=3;
            else if(mod==38) currentTime+=2;
        }
    }
    return 0;
}
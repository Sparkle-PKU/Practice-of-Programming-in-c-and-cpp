/*魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。 
红司令部，City 1，City 2，……，City n，蓝司令部
两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。 
双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。 
武士在刚降生的时候有一个生命值。 
在每个整点，双方的司令部中各有一个武士降生。 
红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。 2 3 4 1 0
蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。 3 0 1 2 4
制造武士需要生命元。 
制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。 
【如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个】。如果所有武士都不能制造了，则司令部停止制造武士。
给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下： 
1) 武士降生 
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。（为简单起见，不考虑单词的复数形式
注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。
2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在10点整，红方司令部停止制造武士
输出事件时： 首先按时间顺序输出；同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

输入
第一行是一个整数，代表测试数据组数。
每组测试数据共两行。 
第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<string>names={"dragon","ninja","iceman","lion","wolf"};
vector<int>hps(5,0);
int t=0;

class Commander
{
public:
    string name;
    int hp;
    vector<int>order;
    vector<int>soldier_hps;
    unordered_map<string, int>total;
    int index;
    int current_step;
    Commander(const string str,int h,const vector<int>& soldier_strength,const vector<int>& soldier_order):name(str),hp(h),order(soldier_order),soldier_hps(soldier_strength),current_step(0),index(1)
    {
        for(int i=0;i<5;i++)
        {
            total[names[i]]=0;
        }
    }

    bool make_soldier()
    {
        for(int i=0;i<5;i++)
        {
            int pos=(current_step+i)%5;
            int id=order[pos];
            if(hp>=soldier_hps[id])
            {
                hp-=soldier_hps[id];
                total[names[id]]++;
                printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",t,name.c_str(),names[id].c_str(),index,soldier_hps[id],total[names[id]],names[id].c_str(),name.c_str());
                current_step=(pos+1)%5;
                index++;
                return true;
            }
        }
        return false;
    }
};

int main()
{
    int round;
    cin>>round;
    for(int r=1;r<=round;r++)
    {
        printf("Case:%d\n",r);
        int m;
        cin>>m;
        for(int i=0;i<5;i++)
        {
            cin>>hps[i];
        }
        Commander Red("red",m,hps,{2,3,4,1,0});
        Commander Blue("blue",m,hps,{3,0,1,2,4});
        bool red_flag=true,blue_flag=true;
        bool red_stop_printed=false,blue_stop_printed=false;
        t=0;
        while(red_flag||blue_flag)
        {
            if(red_flag) red_flag=Red.make_soldier();
            if(!red_flag&&!red_stop_printed)
            {
                printf("%03d red headquarter stops making warriors\n",t);
                red_stop_printed=true;
            }
            if(blue_flag) blue_flag=Blue.make_soldier();
            if(!blue_flag&&!blue_stop_printed)
            {
                printf("%03d blue headquarter stops making warriors\n",t);
                blue_stop_printed=true;
            }
            t++;
        }
    }
    return 0;
}
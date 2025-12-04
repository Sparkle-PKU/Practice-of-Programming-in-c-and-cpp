/*写一个程序完成以下命令：
new id ——新建一个指定编号为id的序列(id < 10000)
add id num——向编号为id的序列加入整数
num merge id1 id2——如果id1等于id2,不做任何事，否则归并序列id1和id2中的数，并将id2清空
unique id——去掉序列id中重复的元素
out id ——从小到大输出编号为id的序列中的元素，以空格隔开
输入第一行一个数n，表示有多少个命令( n＜＝２０００００)。以后n行每行一个命令。
按题目要求输出*/
#include <iostream>
#include <list>
#include <string>
#include <string.h>
#include <map>
using namespace std;
int main(void)
{
    int n;
    cin>>n;
    map<int,list<int>>dic;
    for(int i=0;i<n;i++)
    {
        string input;
        cin>>input;
        if(input=="new") //new id
        {
            int id;
            cin>>id;
            dic[id]=list<int>();
        }
        else if(input=="add")//add id num
        {
            int id,num;
            cin>>id>>num;
            dic[id].push_back(num);
        }
        else if(input=="merge")//merge id1 id2
        {
            int id1,id2;
            cin>>id1>>id2;
            if(id1!=id2)
            {
                dic[id1].sort();
                dic[id2].sort();
                dic[id1].merge(dic[id2]);
            }
        }
        else if(input=="unique")//unique id
        {
            int id;
            cin>>id;
            dic[id].sort();
            dic[id].unique();
        }
        else if(input=="out")//out id
        {
            int id;
            cin>>id;
            dic[id].sort();
            for(auto it=dic[id].begin();it!=dic[id].end();it++)
            {
                if(it==dic[id].begin()) cout<<*it;
                else cout<<" "<<*it;
            }
            cout<<endl;
        }
    }
}
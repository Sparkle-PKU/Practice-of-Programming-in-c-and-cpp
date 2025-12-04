/*现有一整数集（允许有重复元素），初始为空。我们定义如下操作：
add x 把x加入集合
del x 把集合中所有与x相等的元素删除
ask x 对集合中元素x的情况询问
对每种操作，我们要求进行如下输出。
add 输出操作后集合中x的个数
del 输出操作前集合中x的个数
ask 先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。
输入
第一行是一个整数n，表示命令数。0<=n<=100000。
后面n行命令，如Description中所述。
输出
共n行，每行按要求输出。*/
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;
int main(void)
{
    int n;
    cin>>n;
    multiset<int>s;
    unordered_map<int,int>had;
    for(int i=0;i<n;i++)
    {
        string command;
        int x;
        cin>>command>>x;
        if(command=="add") 
        {
            s.insert(x);
            had[x]=1;
            cout<<s.count(x)<<endl;
        }
        else if(command=="del") 
        {
            cout<<s.count(x)<<endl;
            s.erase(x);
        }
        else
        {
            cout<<had[x]<<" "<<s.count(x)<<endl;
        }
    }
    return 0;
}
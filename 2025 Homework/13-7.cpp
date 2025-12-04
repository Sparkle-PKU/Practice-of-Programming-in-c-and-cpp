/*我们定义一个正整数a比正整数b优先的含义是：
*a的质因数数目（不包括自身）比b的质因数数目多；
*当两者质因数数目相等时，数值较大者优先级高。
现在给定一个容器，初始元素数目为0，之后每次往里面添加10个元素，每次添加之后，要求输出优先级最高与最低的元素，并把该两元素从容器中删除。
输入第一行: num (添加元素次数，num <= 30)
下面10*num行，每行一个正整数n（n < 10000000).
每次输入10个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。*/
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;
int prime(int n)
{
    int count=0;
    int k=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            count++;
            while(n%i==0) n/=i;
        }
    }
    if(n>1&&n!=k) count++;
    return count;
}


template<class T>
class comp
{
public:
    bool operator()(const T a,const T b) const
    {
        if(prime(a)!=prime(b)) return prime(a)>prime(b);
        return a>b;
    }
};
int main(void)
{
    int num;
    cin>>num;
    multiset<int,comp<int>>mset;
    for(int i=0;i<num;i++)
    {
        int nums=0;
        for(int j=0;j<10;j++)
        {
            cin>>nums;
            mset.insert(nums);   
        }
        cout<<*mset.begin()<<" "<<*mset.rbegin()<<endl;
        if(*mset.begin()==*mset.rbegin()) mset.erase(*mset.begin());
        else
        {
            mset.erase(*mset.begin());
            mset.erase(*mset.rbegin());
        }
    }
    return 0;
}
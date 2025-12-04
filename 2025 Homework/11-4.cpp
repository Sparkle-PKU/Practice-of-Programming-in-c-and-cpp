/*读入两个整数，输出两个整数 ，直到碰到-1
输入多组数据，每组一行，是两个整数
对每组数据，原样输出 
当碰到输入中出现-1 时，程序结束 
输入中保证会有 -1*/
#include <iostream>
using namespace std;
class MyCin
{
    bool stop;
public:
    MyCin(){stop=false;}
    operator bool()
    {
        return !stop;
    }
    MyCin& operator>>(int &n)
    {
        cin>>n;
        if(n==-1) stop=true;
        return *this;
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
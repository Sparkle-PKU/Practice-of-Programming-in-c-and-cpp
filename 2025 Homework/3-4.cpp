/*写一个二维数组类 Array2,使得下面程序的输出结果是：
0,1,2,3,
4,5,6,7,
8,9,10,11,
next
0,1,2,3,
4,5,6,7,
8,9,10,11,
*/
#include <iostream>
#include <cstring>
using namespace std;

class Array2 
{
public:
    int l,w; 
    int** arr=nullptr;
    Array2(int x=0,int y=0)//用缺省值，避免l、w未定义
    {
        l=x;
        w=y;
        arr=new int*[l];
        for(int i=0;i<l;i++)
        {
            arr[i]=new int[w];
        }

    }
    ~Array2()
    {
        for(int i=0;i<l;i++) delete[]arr[i];
        delete[]arr;
    }
    Array2& operator= (const Array2& vec)
    {
        if(this==&vec) return *this;//一定小心自我赋值！！！必须特判
        for(int i=0;i<l;i++) delete[]arr[i];
        delete[]arr;
        l=vec.l;
        w=vec.w;
        arr=new int*[l];
        for(int i=0;i<l;i++)
        {
            arr[i]=new int[w];
        }
        for(int i=0;i<l;i++)
        {
            for(int j=0;j<w;j++)
            {
                arr[i][j]=vec.arr[i][j];
            }
        }
        return *this;
    }
    int* operator[](int i)//只需要把一维的重载为一个vector<int>,而后第二次访问C++已经实现
    {
        return arr[i];
    }
    int operator() (int i,int j)
    {
        return arr[i][j];
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
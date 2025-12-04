/*实现一个三维数组模版CArray3D，可以用来生成元素为任意类型变量的三维数组，输出指定结果
建议做法：
1. a[i][j][k] 这个表达式的第一个[]返回一个内部类的对象，该内部类也重载了[],且返回值为指针。
2. 必要时需重载对象到指针的强制类型转换运算符*/
#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
public:
    int x;
    class CArray2D
    {
    public:
        T* p;
        int h,w;
        void init(int m,int n)
        {
			h=m,w=n;
            p=new T[m*n];
        }
        T* operator[](int k)
        {
            return p+k*w;
        }
        operator T*()
        {
            return this->p;
        }
    };
    CArray2D* p2;
    CArray3D(int k,int m,int n):x(k)
    {
        p2=new CArray2D[x];
        for(int i=0;i<x;i++)
        {
            p2[i].init(m,n);
        }
    }
    CArray2D& operator[](int k)
    {
        return p2[k];
    }
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k) 
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}
void PrintB()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) 
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];	
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));	
	memset(a[1],-1 ,20*sizeof(int));
	PrintA(); 
	memset(a[1][1],0 ,5*sizeof(int));	
	PrintA();

	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
		
	return 0;
}
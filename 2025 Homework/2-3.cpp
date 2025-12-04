/*程序填空，输出指定结果
输入多组数据，每组一行，是一个整数
对每组数据，输出两行，每行把输入的整数打印两遍*/
#include <iostream>
#include <string>
using namespace std;
class Base {
public:
	int k;
	Base(int n):k(n) { }
};
class Big
{
public:
	int v;
	Base b;
    Big (int n) :b(n){v=n;}
};
int main()
{
	int n;
	while(cin >>n) {
		Big a1(n);
		Big a2 = a1;
		cout << a1.v << "," << a1.b.k << endl;
		cout << a2.v << "," << a2.b.k << endl;
	}
}
/*程序填空，使其按要求输出
输入多组数据，每组一行，是整数 m 和 n
先输出一行123 。然后，对每组数据，输出两行，第一行是m,第二行是n*/
#include <iostream>
using namespace std;
class A {
public:
	int val;
    A(int n=123){val=n;}
    A& GetObj()
    {
        return *this;
    }
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}
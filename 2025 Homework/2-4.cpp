/*程序填空，使其输出9 22 5*/

#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    Sample(int n=0)
    {
        v=n;
    }
    Sample(const Sample& s){v=2+s.v;}
    
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);//9
	Sample c = 20;
	PrintAndDouble(c);//22 f(5)=5,f(20)=22
	Sample d;
	d = a;
	cout << d.v;//5
	return 0;
}
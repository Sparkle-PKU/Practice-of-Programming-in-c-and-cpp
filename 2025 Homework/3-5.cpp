/*程序填空，输出指定结果。输入多组数据，每组数据是两个非负整数s和 n。s最多可能200位， n用int能表示
对每组数据，输出6行，内容对应程序中6个输出语句*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt
{
public:
    int l;
    char num[210];
    CHugeInt(char* s)
    {
        l=strlen(s);
        strcpy(num,s);
        int i=0,j=l-1;
        while(i<j)
        {
			char tmp=s[i];
			num[i]=num[j];
			num[j]=tmp;
			i++;
            j--;
		}
    }
    CHugeInt(int n=0)
    {
        l=0;
		if (n==0) num[l++]='0';
		else
        {
            while(n)
            {
			    num[l++]=n%10+'0';
			    n/=10;
            }
        }
    }
    CHugeInt operator+(const CHugeInt& b)
    {
        CHugeInt temp;
        temp.l=0;
		for(int i=0,j=0,g=0;;)
        {
			if(i>=l&&j>=b.l&&g==0) break;
			int tmp1=0,tmp2=0;
			if(i<l)
            {
                tmp1=num[i]-'0';
                i++;
            }
			if(j<b.l)
            {
                tmp2=b.num[j]-'0';
                j++;
            }
			temp.num[temp.l++]=(tmp1+tmp2+g)%10+'0';
			g=(tmp1+tmp2+g)/10;
		}
		return temp;
    }
    friend CHugeInt operator+(int n,CHugeInt& b)
    {
        CHugeInt temp;
        temp.l=0;
		for(int i=0,j=0,g=0;;)
        {
			if(i>=b.l&&!n&&g==0) break;
			int tmp1=0,tmp2=0;
			if(i<b.l)
            { 
                tmp1=b.num[i]-'0';
                i++;
            }
			if(n)
            {
                tmp2=n%10;
                n/=10;
            }
			temp.num[temp.l++]=(tmp1+tmp2+g)%10+'0';
			g=(tmp1+tmp2+g)/10;
		}
		return temp;
    }
    CHugeInt operator++(void)
    {
        CHugeInt temp=*this;
        temp=1+temp;
        *this=1+*this;
        return temp;
    }
    CHugeInt operator++(int)
    {
        CHugeInt temp=*this;
        *this=1+*this;
        return temp;
    }
    void operator+=(int n)
    {
        *this=*this+n;
        return;
    }
    friend ostream& operator<<(ostream& os,const CHugeInt& b)
    {
        for(int i=b.l-1;i>=0;i--)
        {
            os<<b.num[i];
        }
        return os;
    }
};
int main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
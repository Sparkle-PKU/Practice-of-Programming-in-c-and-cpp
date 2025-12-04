/*补足MyString类，使程序输出指定结果
输入多组数据，每组一行，是两个不带空格的字符串
对每组数据，先输出一行，打印输入中的第一个字符串三次
然后再输出一行，打印输入中的第二个字符串三次*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
	char* getp() const
	{
		return p;
	}
	MyString(const MyString& s)
	{
		p=new char[strlen(s.p)+1];
		strcpy(p,s.p);
	}
    void Copy(MyString w)
    {
		if(w.p==NULL) p=NULL;
		else
		{
			p= new char[strlen(w.p)+1];
			strcpy(p,w.p);
		}
    }
	MyString& operator =(char* s)
	{
		if (p != NULL)delete[] p;
		p = new char[strlen(s) + 1];
		strcpy(p, s);
		return *this;
	}
	MyString& operator =(MyString& s)
	{
		if (p != NULL)delete[] p;
		p = new char[strlen(s.getp()) + 1];
		strcpy(p, s.getp());
		return *this;
	}
	friend ostream& operator <<(ostream& os,MyString& s)
	{
		os<<s.p;
		return os;
	}
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}
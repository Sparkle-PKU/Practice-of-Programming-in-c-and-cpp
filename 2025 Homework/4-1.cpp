/*程序填空，输出如下内容
1. abcd-efgh-abcd-
2. abcd-
3. 
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-
*/
#include <cstdlib>
#include <iostream>
using namespace std;
class MyString
{
public:
    char* str;
    MyString(void)
    {
        str=new char[1];
        str[0]='\0';//凡string问题，务必小心末尾的'0'!!!
    }
    MyString(const char* s)
    {
        int len=strlen(s);
        str=new char[len+1];
        for(int i=0;i<len;i++)
        {
            str[i]=s[i];
        }
    }
    MyString(const MyString& other)//默认是浅拷贝，这里要改成深拷贝
    {
        int len=strlen(other.str);
        str=new char[len+1];
        strcpy(str,other.str);
    }
    ~MyString(){delete []str;}
    bool operator<(MyString s)
    {
        int len=strlen(s.str)>strlen(str)?strlen(str):strlen(s.str);
        for(int i=0;i<len;i++)
        {
            if(str[i]<s[i]) return true;
            if(str[i]>s[i]) return false;
        }
        return strlen(str)<strlen(s.str);
    }
    bool operator==(MyString s)
    {
        return !strcmp(str,s.str);
    }
    bool operator>(MyString s)
    {
        int len=strlen(s.str)>strlen(str)?strlen(str):strlen(s.str);
        for(int i=0;i<len;i++)
        {
            if(str[i]>s[i]) return true;
            if(str[i]<s[i]) return false;
        }
        return strlen(str)>strlen(s.str);
    }
    friend ostream& operator<<(ostream& os,MyString s)
    {
        int len=strlen(s.str);
        for(int i=0;i<len;i++)
        {
            os<<s.str[i];
        }
        return os;
    }
    char& operator[](int i)
    {
        return str[i];
    }
    MyString operator+(MyString s)
    {
        int len=strlen(str)+strlen(s.str);
        char* newStr=new char[len+1];
        strcpy(newStr,str);
        strcat(newStr,s.str);
        MyString temp(newStr);
        delete[] newStr;
        return temp;
    }
    
    friend MyString operator+(const char* s1,MyString s2)
    {
        int len=strlen(s1)+strlen(s2.str);
        char* newStr=new char[len+1];
        strcpy(newStr,s1);
        strcat(newStr,s2.str);
        MyString temp(newStr);
        delete[] newStr;
        return temp;
    }
    
    friend MyString operator+(MyString s1,const char* s2)
    {
        int len=strlen(s1.str)+strlen(s2);
        char* newStr=new char[len+1];
        strcpy(newStr,s1.str);
        strcat(newStr,s2);
        MyString temp(newStr);
        delete[] newStr;
        return temp;
    }
    
    MyString& operator=(MyString s)
    {
        if(this==&s) return *this;
        delete[] str;
        str=new char[strlen(s.str)+1];
        strcpy(str,s.str);
        return *this;
    }
    
    void operator+=(MyString s)
    {
        int len=strlen(str)+strlen(s.str);
        char* newStr=new char[len+1];
        strcpy(newStr,str);
        strcat(newStr,s.str);
        delete[] str;
        str=newStr;
    }
    
    char* operator()(int index,int len)
    {
        char* substr=new char[len+1];
        for(int i=0;i<len;i++)
        {
            substr[i]=str[index+i];
        }
        substr[len]='\0';
        return substr;
    }
    
};


int CompareString(const void * e1,const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if(*s1<*s2) return -1;
	else if(*s1==*s2) return 0;
	else if(*s1>*s2) return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	//s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}
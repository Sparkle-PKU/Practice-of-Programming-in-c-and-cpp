/*程序填空，使得下面的程序,先输出
(Tom,80),(Tom,70),(Jone,90),(Jack,70),(Alice,100),
(Tom,78),(Tom,78),(Jone,90),(Jack,70),(Alice,100),
(70,Jack),(70,Tom),(80,Tom),(90,Jone),(100,Alice),
(70,Error),(70,Error),(80,Tom),(90,Jone),(100,Alice),
******
然后，再根据输入数据按要求产生输出数据
输入数据的每一行，格式为以下之一：
A name score
Q name score
name是个不带个空格的字符串，长度小于 20
score是个整数，能用int表示
A name score 表示往数据库中新增一个姓名为name的学生，其分数为score。开始时数据库中一个学生也没有。
Q name 表示在数据库中查询姓名为name的学生的分数。数据保证学生不重名。
输入数据少于200,000行。
对于每个查询，输出学生的分数。如果查不到，则输出 "Not Found"*/
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
template<class T1,class T2,class F=greater<T1>>
class MyMultimap
{
private:
    multimap<T1,T2,F>mmap;
public:
    typedef typename multimap<T1,T2,F>::iterator iterator;
    MyMultimap()
    {
        mmap.clear();
    }
    void insert(pair<T1,T2>mpair)
    {
        mmap.insert(mpair);
    }
    auto begin()
    {
        return mmap.begin();
    }
    auto end()
    {
        return mmap.end();
    }
    void Set(T1 key,T2 value)
    {
        for(auto it=mmap.begin();it!=mmap.end();it++)
        {
            if(it->first==key)
            {
                it->second=value;
            }
        }
    }
    auto find(const T1 key)
    {
        return mmap.find(key);
    }
    void clear()
    {
        mmap.clear();
    }
};
template <typename T1,typename T2>
ostream& operator<<(ostream& os,pair<T1,T2>&p)
{
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}
struct Student 
{
	string name;
	int score;
};
template <class T>
void Print(T first,T last) {
	for(;first!= last; ++ first)
		cout << * first << ",";
	cout << endl;
}
int main()
{
	
	Student s[] = { {"Tom",80},{"Jack",70},
					{"Jone",90},{"Tom",70},{"Alice",100} };
	
	MyMultimap<string,int> mp;
	for(int i = 0; i<5; ++ i)
		mp.insert(make_pair(s[i].name,s[i].score));
	Print(mp.begin(),mp.end()); //按姓名从大到小输出

	mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
	Print(mp.begin(),mp.end());
	
	
	
	MyMultimap<int,string,less<int> > mp2;
	for(int i = 0; i<5; ++ i) 
		mp2.insert(make_pair(s[i].score,s[i].name));
	
	Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
	mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
	Print(mp2.begin(),mp2.end());
	cout << "******" << endl;
	
	mp.clear();
	
	string name;
	string cmd;
	int score;		
	while(cin >> cmd ) {
		if( cmd == "A") {
			cin >> name >> score;
			if(mp.find(name) != mp.end() ) {
				cout << "erroe" << endl;
			}
			mp.insert(make_pair(name,score));
		}
		else if(cmd == "Q") {
			cin >> name;
			MyMultimap<string,int>::iterator p = mp.find(name);
			if( p!= mp.end()) {
				cout << p->second << endl;
			}
			else {
				cout << "Not Found" << endl; 
			}		
		}
	}
	return 0;
}
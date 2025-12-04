/*给定n个字符串（从1开始编号），每个字符串中的字符位置从0开始编号，长度为1-500，现有如下若干操作：
copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
reset S N：将第N个字符串变为S。
print N：打印输出第N个字符串。
printall：打印输出所有字符串。
over：结束操作。
其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。
输入第一行为一个整数n（n在1-20之间）
接下来n行为n个字符串，字符串不包含空格及操作命令等。
接下来若干行为一系列操作，直到over结束。
根据操作提示输出对应字符串。*/
#include <iostream>
#include <string>
using namespace std;
auto parse(string command,vector<string>&str)
{
    int id=command.find(' ');
    string cmd;
    if(0<=id&&id<command.size()) cmd=command.substr(0,id);
    else cmd=command;
    if(cmd=="copy")
    {

    }
    else if(cmd=="add")
    {
        
    }
    else if(cmd=="find")
    {

    }
    else if(cmd=="rfind")
    {

    }
    else if(cmd=="insert")
    {

    }
    else if(cmd=="reset")
    {

    }
    else if(cmd=="print")
    {

    }
    else if(cmd[0]>='0'&&cmd[0]<='9')
    {
        return int(cmd);
    }
}
int main(void)
{
    int n;
    vector<string>str(n,string());
    for(int i=0;i<n;i++)
    {
        cin>>str[i];
    }
    string command;
    while(getline(cin,command))
    {
        if(command=="over") break;
        else if(command=="printall")
        {
            for(int i=0;i<n;i++)
            {
                cout<<str[i]<<endl;
            }
        }
        else parse(command,str);
    }
    return 0;
}
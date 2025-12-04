/*逆波兰表示法（Reverse Polish Notation，简称 RPN），是源自1920年波兰数学家 Jan Łukasiewicz 提出的波兰表示法（前缀表达式）的一种变体。RPN 是一种将操作符写在操作数之后的数学表示法，因此也称为后缀表示法。
在 RPN 表示法中，操作符写在其操作数之后。例如，普通中缀表达式 “3 + 4” 在 RPN 中表示为 “3 4 +”。如果有多个操作，操作符始终在其第二个操作数之后。例如，“3 − 4 + 5” 在 RPN 中写作 “3 4 − 5 +”：即先计算 3 减 4，再加上 5。
RPN 的一个优点是不需要使用括号来明确操作顺序。例如，“3 − 4 * 5” 既可以表示 “3 − (4 * 5)”（即 3 减 20），也可以表示 “(3 − 4) * 5”（即 -1 乘 5）。而在后缀表达式中，“3 4 5 * −” 表示的就是前者（即先算 4×5，再用 3 减去结果），表达清晰无歧义。

你需要设计一个简易的 RPN 计算器，它支持以下操作符：
+ 加法
- 减法
* 乘法
/ 除法（除数的绝对值不会小于 10^-9，即不会除以 0）
^ 幂运算（如果底数 b <= 0，指数 e 必须是一个不超过 10^9 的正整数）
你可以假设在计算过程中，所有数值都能被 double 类型表示。
此外，这个计算器还具备“内存”功能：
每次计算一个表达式后，从内存中删除最小的那个数，再把当前表达式的值存入内存。

输入第一行是一个整数 n，表示计算器内存的容量。
接下来的若干行是内存的初始值，一共 n 个浮点数，每行最多 10 个数。
然后是若干行 RPN 表达式，以 = 结尾，表示“开始计算”。每个词（数字或操作符）不超过 20 个字符。

每个表达式结果输出一行。
然后输出一个空行，用于分隔计算结果与内存输出。
最后输出所有内存中的数，升序排列，每行输出 10 个，使用 科学计数法格式（%e），即每个数保留 6 位小数 + 两位指数，例如：
1.234567e+00 2.345678e+01 ...每行之间以空格分隔。*/
#include <iostream>
#include <stack>
#include <string.h>
#include <set>
#include <math.h>
#include <sstream>
using namespace std;
int main(void)
{
    int n;
    scanf("%d\n",&n);
    multiset<double>mset;
    for(int i=0;i<n;i++)
    {
        double num;
        scanf("%lf",&num);
        mset.insert(num);
    }
    cin.ignore();
    string input;
    while(getline(cin,input))
    {
        if(input.empty()) continue;
        stack<double> nums;
        stringstream ss(input);
        string token;
        bool valid=true;
        while(ss>>token)
        {
            if(token=="=") break;

            if(token=="+"||token=="-"||token=="*"||token=="/"||token=="^")
            {
                if(nums.size()<2)
                {
                    valid = false;
                    break;
                }
                double b=nums.top();
                nums.pop();
                double a=nums.top();
                nums.pop();
                if (token=="+") nums.push(a+b);
                else if (token=="-") nums.push(a-b);
                else if (token=="*") nums.push(a*b);
                else if (token=="/") nums.push(a/b);
                else if (token=="^")
                {
                    if(a<=0&&(b>1e9||b!=floor(b)))
                    {
                        valid=false;
                        break;
                    }
                    nums.push(pow(a,b));
                }
            }
            else
            {
                try
                {
                    double val=stod(token);
                    nums.push(val);
                }
                catch (...)
                {
                    valid=false;
                    break;
                }
            }
        }
        double res=nums.top();
        mset.erase(mset.begin());
        mset.insert(res);
        printf("%.6e\n",res);
    }
    printf("\n");
    int count=0;
    for(auto it=mset.begin();it!=mset.end();it++)
    {
        if (count>0) printf(" ");
        printf("%.6e",*it);
        count++;
        if(count==10)
        {
            printf("\n");
            count=0;
        }
    }
    if(count>0) printf("\n");
    return 0;
}
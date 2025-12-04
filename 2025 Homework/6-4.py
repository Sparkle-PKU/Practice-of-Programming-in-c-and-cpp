'''一个最简单的计算器，支持+, -, *, / 四种运算。仅需考虑输入输出为整数的情况(除法结果就是商，忽略余数）
输入只有一行，共有三个参数，其中第1、2个参数为整数，第3个参数为操作符（+,-,*,/）。
输出只有一行，一个整数，为运算结果。然而：
1. 如果出现除数为0的情况，则输出：Divided by zero!
2. 如果出现无效的操作符(即不为 +, -, *, / 之一），则输出：Invalid operator!'''
a,b,c=input().split()
a=int(a)
b=int(b)
if c=='+':
    print(a+b)
elif c=='-':
    print(a-b)
elif c=='*':
    print(a*b)
elif c=='/':
    if(b!=0):
        print(a//b)
    else:
        print("Divided by zero!")
else:
    print("Invalid operator!")

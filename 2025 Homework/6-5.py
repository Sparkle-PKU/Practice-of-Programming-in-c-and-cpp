'''小 A 打算新建一幢楼，这幢楼需要占用一块长方形的面积恰好为 n 平方米的土地，且为了方便测量，这块土地的长宽必须为整数米。
小 A 需要在这幢楼外边修围栏，围栏长度为这块长方形的周长。
现在想要知道最小的围栏长度。
输入一个正整数 n(n ≤ 2 × 109)，表示楼的面积。
输出一个数表示答案。数据保证答案在int范围内。'''
from math import sqrt
from math import ceil
from math import floor
n=int(input())
ans=2*(n+1)
for i in range(1,ceil(sqrt(n))+1):
    if(ceil(n/i)==floor(n/i)):
        ans=min(ans,2*(i+n//i))
print(ans)
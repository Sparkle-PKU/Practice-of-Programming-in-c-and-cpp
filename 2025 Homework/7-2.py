'''一副扑克牌有52张牌，分别是红桃，黑桃，方片，梅花各13张，不包含大小王，现在Alex抽到了n张牌，请将扑克牌按照牌面从大到小的顺序排序。
牌的表示方法：
红桃(heart)用字母h表示
黑桃(spade)用字母s表示
方片(dianmond)用字母d表示
梅花(club)用字母c表示
2~10的牌面直接用2,3,4,5,6,7,8,9,10 表示，其余的分别为A，J，Q，K
比如方片J用dJ表示， 红桃A用hA表示
牌面大小：
2>A>K>Q>J>10>9>……>4>3
相同牌面的按照花色（h>s>d>c）顺序排。

输入多组数据。每组数据一行，表示当前摸到的n张牌（1 < n <=52）。
针对每组数据，输出一行，即排序后的结果。'''
def cmp(x):
    cnt=0
    if x[1:]=="2":
        cnt+=2000
    elif x[1:]=="K":
        cnt+=130
    elif x[1:]=="Q":
        cnt+=120
    elif x[1:]=="J":
        cnt+=110
    elif x[1:]=="A":
        cnt+=1000
    else :
        cnt+=int(x[1:])*10
    if x[0]=="h":
        cnt+=4
    elif x[0]=="s":
        cnt+=3
    elif x[0]=="d":
        cnt+=2
    else:
        cnt+=1
    return cnt
try:
    while True:
        line=input().strip()
        if not line:
            continue
        pokers=line.split()
        pokers.sort(key=cmp, reverse=True)
        print(" ".join(pokers))
except EOFError:
    pass
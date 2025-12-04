'''某校园为方便学生订餐，推出食堂预定系统。食宿平台会在前一天提供菜单，学生在开饭时间前可订餐。 食堂每天会推出m个菜，每个菜有固定的菜价和总份数，售卖份数不能超过总份数。 假设共有n个学生点餐，每个学生固定点3个菜，当点的菜售罄时, 学生就买不到这个菜了。 请根据学生预定记录，给出食堂总的预定收入 数据满足1 <= n <= 6000，3 <= m <= 6000，单品菜价不大于1000元，每个菜的配额不超过3000

输入第一行两个整数n和m，代表有n个学生订餐，共有m个可选的菜
下面m行，每行三个元素，分别是菜名、售价和可提供量，保证菜名不重合，菜价为整数
下面n行，每行三个元素，表示这个学生点的三个菜的菜名
输出一个整数，表示食堂的收入'''
n,m=map(int,input().split())
count=dict()
price_tag=dict()
for _ in range(m):
    name,price,num=map(str,input().split())
    price=int(price)
    num=int(num)
    count[name]=num
    price_tag[name]=price
sold=0
for _ in range(n):
    a1,a2,a3=map(str,input().split())
    if(count[a1]>=1):
        sold+=price_tag[a1]
        count[a1]-=1
    if(count[a2]>=1):
        sold+=price_tag[a2]
        count[a2]-=1
    if(count[a3]>=1):
        sold+=price_tag[a3]
        count[a3]-=1
print(sold)
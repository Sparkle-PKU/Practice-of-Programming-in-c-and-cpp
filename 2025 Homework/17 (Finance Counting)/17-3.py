'''交易统计:文件finance.xlsx中记录了2019年3月某公司员工的交易额, 请你找出单日交易总额最小的三天, 并查看这三天是周几。每人每次交易额均为整数。
输出格式:三行，按照交易额从小到大排序，每行格式为日期、交易额、周几，用空格隔开。
样例：
2023-06-05 1000 Monday
2023-06-01 2000 Thursday
2023-06-11 3000 Sunday
'''
import pandas as pd
import datetime
pd.set_option('display.unicode.east_asian_width',True)
dt=pd.read_excel("finance.xlsx",sheet_name="Sheet1",index_col=0)
df=dt
daily_total={}
for i in range(len(df)):
    date=str(df.iloc[i]['日期'])[:10]
    value=float(df.iloc[i]['交易额'])
    if pd.isnull(value):
        value=0
    if date not in daily_total.keys():
        daily_total[date]=value
    else:
        daily_total[date]=daily_total[date]+value
res=sorted(daily_total.items(),key=lambda x: x[1])
for i in range(3):
    print(f"{res[i][0]} {int(res[i][1])} {datetime.datetime.strptime(res[i][0],'%Y-%m-%d').strftime('%A')}")


'''交易统计:文件finance.xlsx中记录了2019年3月某公司员工的交易额, 请你找出单日交易总额最小的三天, 并查看这三天是周几。每人每次交易额均为整数。
输出格式:三行，按照交易额从小到大排序，每行格式为日期、交易额、周几，用空格隔开。
样例：
2023-06-05 1000 Monday
2023-06-01 2000 Thursday
2023-06-11 3000 Sunday
'''
import pandas as pd
pd.set_option('display.unicode.east_asian_width',True)
dt=pd.read_excel("finance.xlsx",sheet_name=['Sheet1'],index_col=0)
df=dt['Sheet1']
df['日期']=pd.to_datetime(df['日期'])
daily_total=df.groupby('日期')['交易额'].sum().reset_index()
daily_total['周几']=daily_total['日期'].dt.day_name()
result=daily_total.nsmallest(3,'交易额')
for _, row in result.iterrows():
    print(f"{row['日期'].date()} {int(row['交易额'])} {row['周几']}")
'''下面程序输入正整数n和m，输出从0开始的前m个n的倍数，请写出times函数的内部实现。不得使用列表、元组、集合、字典，times必须是个生成器函数。
输入两个整数 n和m
输出n的前m个倍数（从0开始)'''
exit = None
def times(n):
	temp=0
	while True:
		yield temp
		temp+=n
	
n,m = map(int,input().split())
seq = times(n)
if str(type(seq) == "<class 'generator'>"):
	i = 0
	for x in seq:
		print(x)
		i += 1
		if i == m:
			break
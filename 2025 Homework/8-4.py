'''程序填空，完成函数cons,按要求输出结果
输入第一行是两个字符串,用空格隔开
第二行是一个整数n
如果n 为0，则输出第一个字符串
如果n 为1，则输出第二个字符串
如果n 为其它数，则输出error'''
def cons(x,y):
	s = a = b = None #防止作弊用
	def f(n):
		if n==0:
			return x
		elif n==1:
			return y
		else:
			return "error"
	return f
s = input().split()
a,b = s[0],s[1]
pair = cons(a,b)
print(pair(int(input())))
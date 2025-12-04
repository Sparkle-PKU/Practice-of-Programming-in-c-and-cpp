'''程序填空
输入三个整数a,b,c
先输出一行True
然后依次输出 a < b， a >= c , a < c 三个表达式的值(True或False)'''
class A:
	def __init__(self,x):
		self.x = x
	def __lt__(self,other):
		if(isinstance(other,int)):
			return self.x<other
		return self.x<other.x
	def __ge__(self,other):
		return self.x>=other.x
a,b,c = map(int,input().split())
print(isinstance(A(2),A))
print(A(a) < A(b))
print(A(a) >= A(c))
print(A(a) < c)
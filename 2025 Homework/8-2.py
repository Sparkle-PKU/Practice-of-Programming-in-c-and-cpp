'''Python支持高阶函数，即函数可以作为函数的参数和返回值
下面程序的combine函数 combine(f,g)能得到一个新函数k, k(x) = f(g(x))，请填空
输入整数n
输出第一行是 (2*n)*(2*n)的值
第二行是 (2*(2*n)) * (2*(2*n)) 的值'''
def combine(f,g):
    return lambda x:f(g(x))
def square(x):
	return x * x
def double(x):
	return x + x
n = int(input())
f = combine(square,double)
#提示： f(x) = square(double(x))
print(f(n))
g = combine(f,double)
#提示: g(x) = f(double(x))
print(g(n))
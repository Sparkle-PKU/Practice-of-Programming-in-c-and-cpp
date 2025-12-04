'''编写一个函数累加器accfunc
输入多组数据，每组2行
第一行形如：
p_1 p_2 p_3 ....p_n
p_i 是个字符串，值是 "f1", "f2", "f3", "f4", "f5" 中间的任何一个，代表程序中相应函数
这一行项数不定，至少有1项
第二行是个整数x
对每组数据，输出以下函数调用的结果:
p_n(p_n-1(...(p2(p1(x)...)
对每组数据，输出以下函数调用的结果:
p_n(p_n-1(...(p2(p1(x)...)'''
def accfunc(f):
    #pylint:skip-file
    def wrapper(g=None):
        if g is None:
            return f
        return accfunc(lambda x: g(f(x)))#用lambda捆绑嵌套
    return wrapper#返回一个捆绑函数接受函数作为参数，或者一个函数f
def f1(x):
    return x + 1
def f2(x):
    return x * x
def f3(x):
    return x + x
def f4(x):
    return x*3
def f5(x):
    return x-4

while True:
    try:
        s = input()
        n = int(input())
        s = s.split()
        k = accfunc
        for x in s:
            k = k(eval(x))
        print(k()(n))
    except:  #读到 eof产生异常
        break
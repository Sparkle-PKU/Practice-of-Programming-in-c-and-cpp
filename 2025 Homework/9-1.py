'''程序填空 程序先输出10(10=1+2+3+4),30， 然后读入若干整数，并输出它们的和
输入多组数据，每组一行，包括不超过100个整数（至少一个），其中第一个整数一定大于0。
对每组数据，输出所有整数的和'''
def mysum(x):
    def f(*args):
        if not args:
            return x
        return mysum(x+int(args[0]))
    return f
def exec(g,i) : #call g for i times
    if i == 1 :
        g()
    else:
        g()
        exec(g,i-1)

k = mysum(1)(2)(3)(4)
k2 = mysum(10)(20)

print(k())
print(k2())

while True:
    try:
        s = input()
        s = s.split()
        k = mysum
        for x in s:
            k = k(int(x))
        exec(k,int(s[0]))
        print(k())
    except:  #读到 eof产生异常
        break
n,m=map(int,input().split())
matrix=[list(map(int,input().split())) for _ in range(n)]
res=[[matrix[i][j] for i in range(n)] for j in range(m)]
for r in res:
    print(" ".join(map(str,r)))
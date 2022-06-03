P=10**9+7;r=range
I=lambda:map(int,input().split())
N,M,Q=I()
A=[*I()];D=[1]+[0]*M;S=[]
for t in A:
 for j in r(M):D[j+1]+=D[j]%P
 for j in r(M-t):D[~j]-=D[~j+~t]%P
for i in r(M+1):
 T=D+[0];S+=[T]
 for j in r(i,M):T[j+1]+=T[j-i]
while Q:t,x=I();C=S[A[t-1]];print((C[M-x]-C[M+~x])%P);Q-=1
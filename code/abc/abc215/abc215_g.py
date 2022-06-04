import bisect
import copy
import decimal
import fractions
import functools
import heapq
import itertools
import math
import random
import sys
from collections import Counter,deque,defaultdict
from functools import lru_cache,reduce
from heapq import heappush,heappop,heapify,heappushpop,_heappop_max,_heapify_max
def _heappush_max(heap,item):
    heap.append(item)
    heapq._siftdown_max(heap, 0, len(heap)-1)
def _heappushpop_max(heap, item):
    if heap and item < heap[0]:
        item, heap[0] = heap[0], item
        heapq._siftup_max(heap, 0)
    return item
from math import degrees, gcd as GCD
read=sys.stdin.read
readline=sys.stdin.readline
readlines=sys.stdin.readlines

def Extended_Euclid(n,m):
    stack=[]
    while m:
        stack.append((n,m))
        n,m=m,n%m
    if n>=0:
        x,y=1,0
    else:
        x,y=-1,0
    for i in range(len(stack)-1,-1,-1):
        n,m=stack[i]
        x,y=y,x-(n//m)*y
    return x,y

class MOD:
    def __init__(self,p,e=1):
        self.p=p
        self.e=e
        self.mod=self.p**self.e

    def Pow(self,a,n):
        a%=self.mod
        if n>=0:
            return pow(a,n,self.mod)
        else:
            assert math.gcd(a,self.mod)==1
            x=Extended_Euclid(a,self.mod)[0]
            return pow(x,-n,self.mod)

    def Build_Fact(self,N):
        assert N>=0
        self.factorial=[1]
        self.cnt=[0]*(N+1)
        for i in range(1,N+1):
            ii=i
            self.cnt[i]=self.cnt[i-1]
            while ii%self.p==0:
                ii//=self.p
                self.cnt[i]+=1
            self.factorial.append((self.factorial[-1]*ii)%self.mod)
        self.factorial_inve=[None]*(N+1)
        self.factorial_inve[-1]=self.Pow(self.factorial[-1],-1)
        for i in range(N-1,-1,-1):
            ii=i+1
            while ii%self.p==0:
                ii//=self.p
            self.factorial_inve[i]=(self.factorial_inve[i+1]*ii)%self.mod

    def Fact(self,N):
        return self.factorial[N]*pow(self.p,self.cnt[N],self.mod)%self.mod

    def Fact_Inve(self,N):
        if self.cnt[N]:
            return None
        return self.factorial_inve[N]

    def Comb(self,N,K,divisible_count=False):
        if K<0 or K>N:
            return 0
        retu=self.factorial[N]*self.factorial_inve[K]*self.factorial_inve[N-K]%self.mod
        cnt=self.cnt[N]-self.cnt[N-K]-self.cnt[K]
        if divisible_count:
            return retu,cnt
        else:
            retu*=pow(self.p,cnt,self.mod)
            retu%=self.mod
            return retu

N=int(readline())
C=list(map(int,readline().split()))
C=Counter(C).values()
mod=998244353
MD=MOD(mod)
MD.Build_Fact(5*10**4)
ans_lst=[0]*N
C=Counter(C)
for i,c in C.items():
    for k in range(1,N+1):
        if N-i-k<0:
            ans_lst[k-1]+=c
        else:
            ans_lst[k-1]+=(1-MD.Fact_Inve(N)*MD.Fact(N-k)%mod*MD.Fact(N-i)%mod*MD.Fact_Inve(N-i-k))*c
        ans_lst[k-1]%=mod
print(*ans_lst,sep="\n")
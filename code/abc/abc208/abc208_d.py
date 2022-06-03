import bisect
import copy
import decimal
import fractions
import heapq
import itertools
import math
import random
import sys
from collections import Counter, deque,defaultdict
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
from math import gcd as GCD
read=sys.stdin.read
readline=sys.stdin.readline
readlines=sys.stdin.readlines

inf = 10**9

N,M=map(int,readline().split())
dist=[[inf]*N for i in range(N)]
for i in range(N):
    dist[i][i]=0
for _ in range(M):
    A,B,C=map(int,readline().split())
    A-=1;B-=1
    dist[A][B]=C
ans=0
for k in range(N):
    for i in range(N):
        for j in range(N):
            if dist[i][j]>dist[i][k]+dist[k][j]:
                dist[i][j]=dist[i][k]+dist[k][j]
            if dist[i][j]!=inf:
                ans+=dist[i][j]
print(ans)
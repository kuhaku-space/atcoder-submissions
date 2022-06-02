MOD = 998244353
N = int(input())
A = list(map(int,input().split()))
A.sort()
ans = A[N-1]**2
t = 0
for i in reversed(range(N-1)):
    ans += A[i]**2
    t += A[i+1]
    ans += A[i] * t
    t *= 2
    t %= MOD
print(ans % MOD)
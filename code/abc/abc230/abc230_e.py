import math

N = int(input())

sq = int(math.sqrt(N))

ans = 0
for i in range(1, sq):
    ans += N // i

sq = N // sq

for i in range(1, sq + 1):
    ans += i * (N // i - N // (i + 1))

print(ans)
n=int(input())

cnt = 0
ans = []
while n != 0:
  while n % 3 != 0:
    n -= 1
    ans.append(cnt)
  n = n // 3
  cnt += 1
print(len(ans))
print(*ans)
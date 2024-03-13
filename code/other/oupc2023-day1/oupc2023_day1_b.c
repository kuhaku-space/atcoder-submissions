s=input()
n=len(s)

ans=n*(n-1)//2

p=0
cnt=-1
for c in s:
  if c == p:
    cnt = 0
  else:
    cnt += 1
    ans -= cnt
  p = c

print(ans%998244353)
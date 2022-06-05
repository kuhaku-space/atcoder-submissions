n, a, b, c, d = map(int, input().split())
s = str(input())

a, b, c, d =a-1, b-1, c-1, d-1

if c < d:
    if s[a:c+1].count('##') > 0 or s[b:d+1].count('##') > 0:
        print('No')
    else:
        print('Yes')
else:
    if s[a:c+1].count('##') > 0 or s[b:d+1].count('##') > 0:
        print('No')
    else:
        if s[b-1:d+2].count('...') > 0:
            print('Yes')
        else:
            print('No')

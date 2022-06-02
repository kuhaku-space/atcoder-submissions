#include <stdio.h>

int main(void) {
    int n, i;
    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        printf("%d %d\n",((i << 1) - 1) % n + 1, (i << 1) % n + 1);
    }

    return 0;
}
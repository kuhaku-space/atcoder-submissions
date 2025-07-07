#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
// long long 型の整数平方根を安全に計算する関数
long long integer_sqrt(long long n) {
    if (n < 0)
        return 0;
    if (n == 0)
        return 0;
    long long x = static_cast<long long>(sqrtl(n));
    while ((x + 1) * (x + 1) <= n) {
        x++;
    }
    while (x * x > n) {
        x--;
    }
    return x;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long N;
    std::cin >> N;
    long long count = 0;
    // ケース1: p^8 の形の数を数える
    // p^8 <= N となる素数 p を探す
    for (long long p = 2;; ++p) {
        // オーバーフローを避けるため、128ビット整数型を使用
        unsigned __int128 val = 1;
        bool overflow = false;
        // p^8 を計算
        for (int i = 0; i < 8; ++i) {
            if (__builtin_mul_overflow(val, p, &val)) {
                overflow = true;
                break;
            }
        }
        // valがNを超えたか、計算中にオーバーフローしたらループを終了
        if (overflow || val > N) {
            break;
        }
        // pが素数かどうかを簡易的にチェック (この範囲ではこれで十分)
        bool is_p_prime = true;
        for (long long i = 2; i * i <= p; ++i) {
            if (p % i == 0) {
                is_p_prime = false;
                break;
            }
        }
        if (is_p_prime) {
            count++;
        }
    }
    // ケース2: p^2 * q^2 の形の数を数える (p < q)
    // (p*q)^2 <= N <=> p*q <= sqrt(N)
    long long limit = integer_sqrt(N);
    // limitまでの素数をエラトステネスの篩で列挙
    std::vector<bool> is_prime(limit + 1, true);
    if (limit >= 0)
        is_prime[0] = false;
    if (limit >= 1)
        is_prime[1] = false;
    for (long long p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (long long i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }
    std::vector<long long> primes;
    for (long long p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
    // 素数のペア (p, q) を効率的に数える
    for (size_t i = 0; i < primes.size(); ++i) {
        long long p = primes[i];
        // 最適化: p^2 * q^2 <= N で q > p であるため, p^4 < N が必要。
        // p^4 > N となったら、それ以降のpでは条件を満たすqは存在しない。
        if (p > integer_sqrt(integer_sqrt(N))) {
            break;
        }
        long long val_p2 = p * p;
        // q <= sqrt(N / p^2) を満たす素数 q (ただし q > p) を数える
        long long q_limit = integer_sqrt(N / val_p2);
        // primesの中から p より大きく q_limit 以下である素数の数を数える
        // upper_bound で q_limit より「大きい」最初の要素を探す
        auto it_upper = std::upper_bound(primes.begin() + i + 1, primes.end(), q_limit);
        // pより大きい素数の開始位置は primes[i+1] なので、そのイテレータは primes.begin() + i + 1
        auto it_lower = primes.begin() + i + 1;
        // 2つのイテレータの間の距離が、条件を満たす q の個数となる
        count += std::distance(it_lower, it_upper);
    }
    std::cout << count << std::endl;
    return 0;
}

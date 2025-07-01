#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
// LとRをグローバル変数として保持
long long L, R;
/**
 * @brief [L+1, R] の範囲にある素数のべき乗 p^k (k >= 2) を数えます。
 *
 * sqrt(R) までの素数をエラトステネスの篩で求め、それぞれのべき乗が
 * [L+1, R] の範囲に含まれるかを確認します。
 * 素数pのべき乗p^kは、pが異なれば値も異なるため重複は発生しません。
 *
 * @return long long [L+1, R] の範囲にある p^k (k>=2) の個数。
 */
long long count_prime_powers_ge2() {
    long long count = 0;  // std::set の代わりに高速なカウンタを使用
    long long limit = sqrtl(R);
    // limitまでの素数をエラトステネスの篩で求める
    std::vector<bool> is_prime_sieve(limit + 1, true);
    if (limit >= 0)
        is_prime_sieve[0] = false;
    if (limit >= 1)
        is_prime_sieve[1] = false;
    for (long long p = 2; p * p <= limit; ++p) {
        if (is_prime_sieve[p]) {
            for (long long i = p * p; i <= limit; i += p) {
                is_prime_sieve[i] = false;
            }
        }
    }
    // 素数 p のべき乗 p^k (k>=2) を列挙
    for (long long p = 2; p <= limit; ++p) {
        if (is_prime_sieve[p]) {
            unsigned __int128 val = p;
            // val * p がオーバーフローしないかチェック
            if (val > (unsigned __int128)R / p)
                continue;
            val *= p;  // これで val = p^2
            while (true) {
                if (val > L && val <= R) {
                    count++;  // カウンタをインクリメント
                }
                if (val > (unsigned __int128)R / p)
                    break;
                val *= p;
            }
        }
    }
    return count;
}
/**
 * @brief [L+1, R] の範囲にある素数 (p^1) を数えます。
 *
 * 区間篩を用いて、指定された範囲の素数を効率的に数えます。
 *
 * @return long long [L+1, R] の範囲にある素数の個数。
 */
long long count_primes_in_range() {
    long long start = L + 1;
    if (start > R) {
        return 0;
    }
    long long limit = sqrtl(R);
    std::vector<long long> small_primes;
    // limit までの素数を求める
    std::vector<bool> is_prime_sieve(limit + 1, true);
    if (limit >= 0)
        is_prime_sieve[0] = false;
    if (limit >= 1)
        is_prime_sieve[1] = false;
    for (long long p = 2; p <= limit; ++p) {
        if (is_prime_sieve[p]) {
            small_primes.push_back(p);
            if (p * p <= limit) {
                for (long long i = p * p; i <= limit; i += p) {
                    is_prime_sieve[i] = false;
                }
            }
        }
    }
    long long count = 0;
    long long block_size = 100000;
    for (long long low = start; low <= R; low += block_size) {
        long long high = std::min(low + block_size - 1, R);
        if (low > high)
            break;
        std::vector<bool> block(high - low + 1, true);
        if (low == 1) {
            block[0] = false;
        }
        for (long long p : small_primes) {
            if (p * p > high)
                break;
            long long start_idx = (low + p - 1) / p;
            long long j = std::max(start_idx, p) * p;
            for (; j <= high; j += p) {
                if (j >= low) {
                    block[j - low] = false;
                }
            }
        }
        for (long long i = 0; i <= high - low; ++i) {
            if (block[i]) {
                count++;
            }
        }
    }
    return count;
}
int main() {
    // 高速化のための設定
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cin >> L >> R;
    if (L == R) {
        std::cout << 1 << std::endl;
        return 0;
    }
    long long ans = 1;
    long long count_ge2 = count_prime_powers_ge2();
    long long count_eq1 = count_primes_in_range();
    ans += count_ge2 + count_eq1;
    std::cout << ans << std::endl;
    return 0;
}

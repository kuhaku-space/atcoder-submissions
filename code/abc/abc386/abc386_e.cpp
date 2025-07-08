#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// グローバル変数
int N;
long long K;
vector<unsigned long long> A;
// 組み合わせのXOR和を格納するベクター
vector<unsigned long long> combination_xors;

/**
 * @brief index以降の要素からcount個選ぶ組み合わせを再帰的に探索し、そのXOR和を列挙する
 * * @param index 現在注目しているAの要素のインデックス
 * @param count あと選ぶ必要がある要素の数
 * @param current_xor 現在までのXOR和
 */
void find_combinations(int index, int count, unsigned long long current_xor) {
    // ベースケース1: 必要な個数(count)を選び終わったら、結果を保存して終了
    if (count == 0) {
        combination_xors.push_back(current_xor);
        return;
    }
    // ベースケース2: 残りの全要素を選んでもcountに満たない場合は、探索を打ち切る（枝刈り）
    if (N - index < count) {
        return;
    }

    // 再帰ステップ
    // 1. A[index] を選ばない場合
    find_combinations(index + 1, count, current_xor);
    // 2. A[index] を選ぶ場合
    find_combinations(index + 1, count - 1, current_xor ^ A[index]);
}

int main() {
    // 高速化のための標準入出力設定
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 入力
    cin >> N >> K;
    A.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // C(N, K) = C(N, N-K) の性質を利用し、探索する組み合わせの数を最小化する
    // K と N-K のうち、小さい方を m とする
    int m = K;
    bool use_complement = false;  // 全体XORを使うかどうかのフラグ
    if (K > N - K) {
        m = N - K;
        use_complement = true;
    }

    // m個の要素を選ぶ組み合わせのXOR和を全列挙する
    // combination_xors に C(N, m) 個の結果が格納される
    find_combinations(0, m, 0);

    unsigned long long max_xor_sum = 0;

    if (use_complement) {
        // N-K が小さい場合 (K個選ぶ代わりに、N-K個"選ばない"ものを考える)
        // S_K = (全要素のXOR和) ^ (選ばなかったN-K個のXOR和)

        // まず、Aの全要素のXOR和を計算
        unsigned long long total_xor = 0;
        for (unsigned long long val : A) {
            total_xor ^= val;
        }

        // 列挙した「選ばなかったN-K個」のXOR和を使い、
        // 「選んだK個」のXOR和を計算し、最大値を求める
        for (unsigned long long xor_sum_m : combination_xors) {
            max_xor_sum = max(max_xor_sum, total_xor ^ xor_sum_m);
        }
    } else {
        // K が小さい場合
        // 列挙したK個の組み合わせのXOR和の中から最大値を探す
        for (unsigned long long xor_sum_k : combination_xors) {
            max_xor_sum = max(max_xor_sum, xor_sum_k);
        }
    }

    // 結果の出力
    cout << max_xor_sum << endl;

    return 0;
}

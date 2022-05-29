#include <iostream>
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <tuple>
#include <utility>
#include <functional>
#include <sys/time.h>
#include <iomanip>

using namespace std;
using ll = long long;
using ld = long double;
#define REP(i, m, n) for(int i = (m); i < (n); ++i)
#define REPR(i, m, n) for(int i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repr(i, n) REPR(i, n-1, 0)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

constexpr int N = 50;
constexpr int M = 2500;
array<array<int, N>, N> A;

array<array<bool, N>, N> visitable;

bool in_board(int x, int y){
	return x >= 0 && x < N && y >= 0 && y < N;
}

int eval(int x, int y){
	int res = A[x][y];
	rep(i, 4){
		x += dx[i], y += dy[i];
		if (in_board(x, y) && !visitable[x][y]) res++;
		x -= dx[i], y -= dy[i];
	}
	return res;
}

int main(void){
	int tmp;
	cin >> tmp >> tmp;
	rep(i, N) rep(j, N) cin >> A[i][j];
	rep(i, N) rep(j, N) visitable[i][j] = false;
	visitable[0][0] = true;
	queue<pair<ll, ll>> que;
	que.push({0, 0});

	int r = 0, c = 0;
	rep(_, M - 1){
		while(!que.empty()){
			auto p = que.front();
			que.pop();
			int x = p.first, y = p.second;
			if(A[x][y] == 9){
				rep(k, 4){
					x += dx[k], y += dy[k];
					if (in_board(x, y) && !visitable[x][y]){
						visitable[x][y] = true;
						que.push({x, y});
					}
					x -= dx[k], y -= dy[k];
				}
			}
		}

		int max = 0;
		repr(i, N){
			repr(j, N){
				if(visitable[i][j] && A[i][j] != 9 && chmax(max, eval(i, j))) r = i, c = j;
			}
		}

		cout << "1 " << r << " " << c << endl;
		A[r][c]++;
		que.push({r, c});
	}

	cout << "2 0 0" << endl;

	return 0;
}

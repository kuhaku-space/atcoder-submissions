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
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define rep(i, n) REP(i, 0, n)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

struct Xorshift {
	unsigned int x, y, z, w;
	
	Xorshift() {
		x = 123456789, y = 362436069, z = 521288629, w = 88675123;
	}

	unsigned int rand(){
		unsigned int t = (x^(x<<11));
		x = y; y = z; z = w;
		return w = (w^(w>>19))^(t^(t>>8));
	}
};
Xorshift xor128;

constexpr int N = 200;
int X[N], Y[N];

double dist(int i, int j){
	return sqrt(pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));
}

double score(array<int, N> &c){
	double ans = 0;
	double mean = 0;
	array<double, N> d;
	rep(i, N){
		d[i] = dist(c[i], c[(i + 1) % N]);
		mean += d[i];
	}
	mean /= N;

	rep(i, N) ans += pow(d[i] - mean, 2);
	return ans / N;
}

array<int, N> build(double d){
	unordered_set<ll> ust;
	rep(i, N) ust.insert(i);

	array<int, N> res;
	rep(i, N){
		if(i == 0){
            ll r = xor128.rand() % N;
			res[0] = r;
			ust.erase(r);
			continue;
		}
		int id = 0;
		double min = LINF;
		for(int j : ust) if(chmin(min, abs(dist(res[i-1], j) - d))) id = j;
		res[i] = id;
		ust.erase(id);
	}
	return res;
}

int main(void){
	clock_t st, en;
	st = clock();
	en = clock();

	int tmp;
	cin >> tmp;
	rep(i, N) cin >> X[i] >> Y[i];

	array<int, N> c, ans;
	double min = LINF, d = 200;
	while((double)(en - st) / CLOCKS_PER_SEC < 1.995){
		c = build(d);
		d += 0.005;
		if(chmin(min, score(c))) ans = c;
		en = clock();
	}
	cerr << d << endl;
	for(int i : ans) cout << i << endl;

	return 0;
}

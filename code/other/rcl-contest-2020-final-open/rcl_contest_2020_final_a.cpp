/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<int>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
using Graph = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define REP(i, m, n) for(int (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(int (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(int (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(int (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
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
template <typename T>
void cosp(const T n){cout << n << ' ';}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << endl;}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << endl;}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << endl;}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1);
constexpr ld EPS = 1e-11;

int N = 500, M = 5000;
int pos = 0;
int d, v, x;
Vec dice = {1, 2, 3, 4, 5, 6};
Vec score(6, INF);
Vec board(N+1, 0);

int f(int i){
	i += pos;
	if(i <= N) return i;
	i = 2 * N - i;
	return i;
}

int fillScore(){
	rep(i, 6) score[i] = board[f(dice[i])];

	int min = INF, minPos = 0;
	rep(i, 6) if(chmin(min, score[i])) minPos = i;
	return minPos;
}

void changeDice(int k){
	if(N - pos > 6 * (M - k)){
		int max = 0, maxPos = 6;
		repn(i, 6) if(chmax(max, f(i))) maxPos = i;
		dice[0] = maxPos;
		return;
	}

	rep(i, 5) if(dice[i] != 6){
		dice[i] = 6;
		return;
	}

	if((N - pos) % 6) dice[0] = (N - pos) % 6;
	else dice[0] = 6;
}

void input(){
	cin >> d >> v >> x;
	pos = x;
	board[pos] = v;
	if(pos == N) pos = 0;
}

int main(void){
	cin >> N >> M;
	rep(i, M){
		changeDice(i);
		co(dice);
		input();
	}

	return 0;
}

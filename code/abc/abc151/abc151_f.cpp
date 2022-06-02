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
using Circle2 = pair<Pld, ld>;
struct Pos{ld x, y, z;};
using Circle3 = pair<Pos, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecPld = vector<Pld>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<double>;
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Tree = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

Circle2 min_ball(Pld p, VecPld &point){
	Pld k;
	ld move, maxi;

	auto dist = [](const Pld &a, const Pld &b) -> ld{
		ld dx = a.fs-b.fs;
		ld dy = a.sc-b.sc;
		return sqrt(dx*dx+dy*dy);
	};

	move = 0.5;
	while(move > EPS/100){
		maxi = 0.0;
		for(Pld i : point) if(chmax(maxi, dist(p, i))) k = i;
		p.fs += (k.fs-p.fs)*move;
		p.sc += (k.sc-p.sc)*move;
		move *= 0.999;
	}
	
	return {p, maxi};
}

Circle3 min_ball(Pos p, Vec1<Pos> &point){
	Pos k;
	ld move, maxi;

	auto dist = [](const Pos &a, const Pos &b) -> ld{
		ld dx = a.x-b.x;
		ld dy = a.y-b.y;
		ld dz = a.z-b.z;
		return sqrt(dx*dx+dy*dy+dz*dz);
	};

	move = 0.5;
	while(move > EPS/100){
		maxi = 0.0;
		for(Pos i : point) if(chmax(maxi, dist(p, i))) k = i;
		p.x += (k.x-p.x)*move;
		p.y += (k.y-p.y)*move;
		p.x += (k.z-p.z)*move;
		move *= 0.999;
	}

	return {p, maxi};
}

int main(void){
    ll n;
    cin >> n;
    VecPld p(n);
    rep(i, n) cin >> p[i].fs >> p[i].sc;

    Pld mid = {500.0, 500.0};
    Circle2 ans = min_ball(mid, p);
    setp(10);
    co(ans.sc);

	return 0;
}

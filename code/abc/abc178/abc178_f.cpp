#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
void co() { cout << endl; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << endl; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9L+7;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

template <typename T>
struct extended_priority_queue{
    priority_queue<T> a, b;

    bool empty(){
        return a.empty();
    }

    void insert(T x){
        a.push(x);
    }

    T top(){
        return a.top();
    }

    void pop(){
        erase(a.top());
    }

    void erase(T x){
        b.push(x);
        while(!a.empty() && a.top() == b.top()){
            a.pop();
            b.pop();
        }
    }
};

int main(void){
    ll n;
    cin >> n;
    Vec a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    Vec cnt_a(n + 1), cnt_b(n + 1);
    rep(i, n) cnt_a[a[i]]++;
    rep(i, n) cnt_b[b[i]]++;
    Vec cnt(n + 1);
    rep(i, n + 1) cnt[i] = cnt_a[i] + cnt_b[i];

    rep(i, n + 1){
        if(cnt[i] > n){
            puts("No");
            return 0;
        }
    }
    puts("Yes");

    Vec ans(n);
    using T = tuple<ll, ll, ll>;
    extended_priority_queue<P> pq1, pq2;
    rep(i, n + 1) pq1.insert({cnt[i], i});
    rep(i, n + 1) pq2.insert({cnt_b[i], i});

    rep(i, n){
        pq1.erase({cnt[a[i]], a[i]});
        pq1.insert({--cnt[a[i]], a[i]});
        if(pq1.top().first == n - i){
            P p = pq1.top();
            // ce(i, p.first, p.second);
            pq1.pop();
            ans[i] = p.second;
            pq2.erase({cnt_b[p.second], p.second});
            cnt[p.second]--;
            cnt_b[p.second]--;
            p.first--;
            pq1.insert(p);
            pq2.insert({cnt_b[p.second], p.second});
            continue;
        }
        vector<P> ps;
        while(true){
            P p = pq2.top();
            pq2.pop();
            if(a[i] == p.second){
                ps.push_back(p);
                continue;
            }
            ans[i] = p.second;
            pq1.erase({cnt[p.second], p.second});
            cnt[p.second]--;
            cnt_b[p.second]--;
            p.first--;
            ps.push_back(p);
            pq1.insert({cnt[p.second], p.second});
            break;
        }
        for(P p : ps) pq2.insert(p);
    }
    rep(i, n) cout << ans[i] << ' ';
    cout << endl;

    return 0;
}

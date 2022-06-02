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

template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next_node;
        vector<int> accept;
        vector<int> is_exist;
        int c;
        int common;
        Node(int _c) : c(_c), common(0) {
            next_node.assign(char_size, -1);
            is_exist.assign(26, 0);
        }
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }

    void insert(const string &word, vector<int> cnt, int word_id) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) {
                next_id = nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            for (int j = 0; j < 26; ++j) {
                if (cnt[j]) ++nodes[node_id].is_exist[j];
            }
            --cnt[c];
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
    }
    void insert(const string &word, vector<int> cnt) {
        insert(word, cnt, nodes[0].common);
    }

    int search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < word.size() - 1; i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) {
                return 0;
            }
            node_id = next_id;
        }
        int c = word.back() - base;
        return nodes[node_id].is_exist[c];
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) {
                return -1;
            }
            node_id = next_id;
        }
        return node_id;
    }
};

int main(void){
    ll n;
    cin >> n;
    Trie<26, 'a'> trie;
    vector<string> ss(n);
    rep(i, n){
        string &s = ss[i];
        cin >> s;
        reverse(all(s));
        vector<int> cnt(26);
        for (char c : s) ++cnt[c - 'a'];
        trie.insert(s, cnt);
    }

    ll ans = 0;
    rep(i, n) ans += trie.search(ss[i]);
    co(ans - n);

    return 0;
}

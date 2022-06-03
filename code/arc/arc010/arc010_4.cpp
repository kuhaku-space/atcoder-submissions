#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>
#include <climits>
#include <cstring>

#ifdef NO_UNLOCK_IO
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif
struct FastIO {
	static void scan(double &x) {
		scanf("%lf", &x);
	}
	template <class Integral>
	static void scan(Integral &x) {
		int k, m = 1;
		x = 0;
		for (;;) {
			k = getchar_unlocked();
			if (k == '-') {
				m = -1;
				break;
			}
			else
			if ('0' <= k && k <= '9') {
				x = k - '0';
				break;
			}
		}
		for (;;) {
			k = getchar_unlocked();
			if (k < '0' || k > '9')
				break;

			x = x * 10 + k - '0';
		}
		x *= m;//mul is faster than branch-misprediction penalty (maybe)
	}
	template <class Arithmetic, class... Rest>
	static void scan(Arithmetic &x, Rest&... y) {
		scan(x);
		scan(y...);
	}
	static void print(double x, char c) {
		printf("%.12f%c", x, c);
	}
	static void print(const char *x, char c) {
		printf("%s%c", x, c);
	}
	template <class Integral>
	static void print(Integral x, char c) {
		int s = 0, m = 0;
		char f[20];//Is this faster than "static char" ?
		if (x < 0) {
			m = 1;
			x = -x;
		}
		while (x) {
			f[s++] = x % 10;
			x /= 10;
		}

		if (!s)
			f[s++] = 0;

		if (m) putchar_unlocked('-');
		while (s--)
			putchar_unlocked(f[s] + '0');

		putchar_unlocked(c);
	}
	template <class Arithmetic>
	static void println(Arithmetic x) {
		print(x, '\n');
	}
};



using namespace std;
typedef complex<long long> Point;
const int MAN = 5005, ENEMY = 100005;
const long long INF = LLONG_MAX;
 
namespace std{
    bool operator< (const Point &a, const Point &b) {
        return a.real() < b.real();
    }
};
 
 
int nMan, nEnemy;
Point man[MAN], enemy[ENEMY];
 
bool read() {
    //cin >> nMan;
		FastIO::scan(nMan);
    
    for (int i = 0; i < nMan; i++) {
        int x, y;
        //cin >> x >> y;
				FastIO::scan(x,y);
        man[i] = Point(x, y);
    }
 
    //cin >> nEnemy;
		FastIO::scan(nEnemy);
    for (int i = 0; i < nEnemy; i++) {
        int x, y;
        //cin >> x >> y;
				FastIO::scan(x,y);
        enemy[i] = Point(x, y);
    }
 
    return true;
}
 
 
void topsort(int curr, vector<int> &order,
             bool visited[MAN], vector<int> adj[MAN]) {
    visited[curr] = true;
    for (int i = 0; i < adj[curr].size(); i++)
        if (!visited[adj[curr][i]])
            topsort(adj[curr][i], order, visited, adj);
    order.push_back(curr);
}
 
 
void dfs(int curr, bool visited[MAN], vector<int> adj[MAN]) {
    visited[curr] = true;
    for (int i = 0; i < adj[curr].size(); i++)
        if (!visited[adj[curr][i]])
            dfs(adj[curr][i], visited, adj);
}
 
 
void work() {
    if (nEnemy == 0) {
        cout << 1 << endl;
        return;
    }
 
    vector<int> adj[MAN];
    for (int i = 0; i < nMan; i++)
        adj[i].clear();
 
    sort(enemy, enemy + nEnemy);
    
    for (int i = 0; i < nMan; i++) {
        int idx = lower_bound(enemy, enemy + nEnemy, man[i]) - enemy;
 
        long long minDist = INF;
        for (int j = idx, k = idx - 1; j < nEnemy || k >= 0; j++, k--) {
             if (j < nEnemy) {
                 if ((enemy[j].real() - man[i].real()) * 
                     (enemy[j].real() - man[i].real()) >= minDist)
                     j = nEnemy;
                 else 
                     minDist = min(minDist, norm(enemy[j] - man[i]));
             }
 
             if (k >= 0) {
                 if ((enemy[k].real() - man[i].real()) * 
                     (enemy[k].real() - man[i].real()) >= minDist)
                     k = -1;
                 else
                     minDist = min(minDist, norm(enemy[k] - man[i]));
             }
        }
        
        for (int j = 0; j < nMan; j++)
            if (i != j && norm(man[i] - man[j]) < minDist)
                adj[i].push_back(j);
    }
 
    vector<int> order;
    bool visited[MAN] = {};
    for (int i = 0; i < nMan; i++)
        if (!visited[i])
            topsort(i, order, visited, adj);
    reverse(order.begin(), order.end());
 
    int ans = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < nMan; i++)
        if (!visited[order[i]]) {
            dfs(order[i], visited, adj);
            ans++;
        }
    
    cout << ans << "\n";
}
 
 
int main() {
    read();
    work();
    return 0;
}
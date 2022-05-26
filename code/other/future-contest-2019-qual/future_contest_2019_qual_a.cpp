#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const int MAX_N = 500;
const int MAX_M = 29;

char board[MAX_M][MAX_M] = {};
int result[MAX_M][MAX_M] = {};

typedef struct {
	int x;
	int y;
	int dir;
} obj;

typedef struct{
	int x;
	int y;
	char type;
} item;

void init_board(int m){
	rep(i, m) rep(j, m) board[i][j] = '.';
	rep(i, m){
		board[0][i] = '#';
		board[i][0] = '#';
		board[m-1][i] = '#';
		board[i][m-1] = '#';
	}
}

void init_result(int m){
	rep(i, m){
		rep(j, m) result[i][j] = 0;
	}
}

void one_step(obj& t){
	switch(t.dir){
	    case 0: if(board[t.x-1][t.y] != '#') t.x--; break;
	    case 1: if(board[t.x][t.y+1] != '#') t.y++; break;
	    case 2: if(board[t.x+1][t.y] != '#') t.x++; break;
	    case 3: if(board[t.x][t.y-1] != '#') t.y--; break;
	}
}

obj move(string s, int m){
	obj t = {m/2, m/2, 0};
    int cnt = 0;
	rep(j, s.length()){
        switch(s[j]){
            case 'S':
                one_step(t);
                break;
            case 'R':
                if(board[t.x][t.y] == 'L') t.dir = (t.dir+3)%4;
                else t.dir = (t.dir+1)%4;
                break;
            case 'L':
                if(board[t.x][t.y] == 'R') t.dir = (t.dir+1)%4;
                else t.dir = (t.dir+3)%4;
                break;
            case 'D':
                while(cnt++ < 2) one_step(t);
                break;
            case 'T':
                while(cnt++ < 3) one_step(t);
                break;
        }
	}

	return t;
}

int count_score(int m){
	int res = 0;
	rep(i, m){
		rep(j, m){
			if(result[i][j] == 1) res += 10;
			else if(result[i][j] == 2) res += 3;
			else if(result[i][j] == 3) res += 1;
		}
	}

	return res;
}

item put_one_item(int m){
	char items[] = {'R', 'L', 'D', 'T', '#'};
	item u;
	u.x = rand()%(m-2)+1;
	u.y = rand()%(m-2)+1;
	u.type = board[u.x][u.y];
	if(u.x == u.y == m/2) board[u.x][u.y] = items[rand()%4];
	else board[u.x][u.y] = items[rand()%5];

	return u;
}

int main(void){
	int n, m, l;
	cin >> n >> m >> l;
	vector<string> s(n);
	rep(i, n) cin >> s[i];
	init_board(m);

	int max_score = 0;
	rep(cnt, 1700){
		item u = {m/2, m/2, '.'};
		if(cnt) u = put_one_item(m);
		init_result(m);
		rep(i, n){
			obj t = move(s[i], m);
			result[t.x][t.y]++;
		}

		int score = count_score(m);
		if(score > max_score){
			max_score = score;
		}else board[u.x][u.y] = u.type;
	}

	rep(i, m){
		rep(j, m) cout << board[i][j];
		cout << endl;
	}

	return 0;
}
